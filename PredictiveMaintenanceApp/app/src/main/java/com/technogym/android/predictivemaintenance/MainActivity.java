package com.technogym.android.predictivemaintenance;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;

import com.technogym.android.predictivemaintenance.ml.AnomalyClassifier;
import com.technogym.android.predictivemaintenance.ml.AnomalyClassifierRecognition;
import com.technogym.android.predictivemaintenance.ml.PCA;
import com.technogym.android.predictivemaintenance.ml.PCA_Scores;

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.List;

public class MainActivity extends AppCompatActivity
{
    private static final String TAG = "PredictMaintenance";
    private PCA pca = new PCA();

    private AnomalyClassifier classifier;
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        pca.init();
        classifier = new AnomalyClassifier(this);

        Button btnPCA = findViewById(R.id.btnPCA);
        btnPCA.setOnClickListener((View v) -> pcaExecute());

        Button btnClassifier = findViewById(R.id.btnClassifier);
        btnClassifier.setOnClickListener((View v) -> classifierExecute());
    }
    /*
    Samples[] samples = new Samples[](1024)
    Float[] std_samples = pca.preprocessing(samples);

    float[] samples = new float[1024];

     */

    private void pcaExecute()
    {
        Log.e(TAG, "pcaExecute");
        new Thread(new Runnable(){
            @Override
            public void run()
            {
                Log.e(TAG, "pcaExecute in worker thread");
                float[] samples = new float[1024];
                for(int i=0; i < samples.length; i++)
                    samples[i] = i*0.1f;

                int res = pca.checkTemperature(samples);
                Log.e(TAG, "checkTemperature " + res);

                res = pca.checkOrientation(samples);
                Log.e(TAG, "checkOrientation " + res);

                PCA_Scores scores = pca.execute(samples);
                Log.e(TAG, "result scores: " + scores.toString());
            }
        }).start();
    }

    private void classifierExecute()
    {
        Log.e(TAG, "classifierExecute");
        new Thread(new Runnable(){
            @Override
            public void run()
            {
                Log.e(TAG, "classifierExecute in worker thread");
                List<AnomalyClassifierRecognition> res = classifier.classify(dataForsimulation());
                for(AnomalyClassifierRecognition anomaly : res)
                    Log.e(TAG, "AnomalyClassifierRecognition " + anomaly.toString());
            }

            private int INPUT_SIZE = 224;
            private int PIXEL_SIZE = 3;
            private int IMAGE_MEAN = 0;
            private float IMAGE_STD = 255.0f;

            private ByteBuffer dataForsimulation()
            {
                Bitmap scaledBitmap = Bitmap.createScaledBitmap(((BitmapDrawable) getResources().getDrawable(R.drawable.img1)).getBitmap(), INPUT_SIZE, INPUT_SIZE, false);
                ByteBuffer byteBuffer;
                byteBuffer = ByteBuffer.allocateDirect(4/* dimensione float*/* INPUT_SIZE * INPUT_SIZE * PIXEL_SIZE);
                byteBuffer.order(ByteOrder.nativeOrder());

                int[] intValues = new int[INPUT_SIZE * INPUT_SIZE];
                scaledBitmap.getPixels(intValues, 0, scaledBitmap.getWidth(), 0, 0, scaledBitmap.getWidth(), scaledBitmap.getHeight());
                int pixel = 0;
                for (int i = 0; i < INPUT_SIZE; ++i) {
                    for (int j = 0; j < INPUT_SIZE; ++j) {
                        final int val = intValues[pixel++];
                        byteBuffer.putFloat((((val >> 16) & 0xFF)-IMAGE_MEAN)/IMAGE_STD);
                        byteBuffer.putFloat((((val >> 8) & 0xFF)-IMAGE_MEAN)/IMAGE_STD);
                        byteBuffer.putFloat((((val) & 0xFF)-IMAGE_MEAN)/IMAGE_STD);
                    }
                }

//                Log.e("TEST**","Record Value Capacity: " + byteBuffer.capacity());
//                Log.e("TEST**","Record Value Position: " + byteBuffer.position());
//                Log.e("TEST**","Record Value Limit: " + byteBuffer.limit());
//                Log.e("TEST**","Record Value Remaining: " + byteBuffer.remaining());
//                Log.e("TEST**","Record Value: " + byteBuffer);

                return byteBuffer;
            }
        }).start();
    }
}