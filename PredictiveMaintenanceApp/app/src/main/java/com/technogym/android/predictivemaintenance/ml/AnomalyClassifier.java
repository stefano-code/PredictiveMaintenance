package com.technogym.android.predictivemaintenance.ml;

import android.content.Context;
import android.content.res.AssetFileDescriptor;
import android.content.res.AssetManager;
import android.util.Log;

import org.tensorflow.lite.Interpreter;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.ByteBuffer;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.PriorityQueue;

public class AnomalyClassifier
{
    private static final String TAG = "AnomalyClassifier";

    private float MAX_RESULTS = 3;
    private float THRESHOLD = 0.01f;

    private Context ctx;
    private Interpreter interpreter;
    private List<String> labelList;

    public AnomalyClassifier(Context ctx)
    {
        Interpreter.Options options = new Interpreter.Options();
        options.setNumThreads(5);
        options.setUseNNAPI(true);
        interpreter = new Interpreter(loadModelFile(ctx.getAssets(), "mobilenet_v1_1.0_224.tflite"), options);
        labelList = loadLabelList(ctx.getAssets(), "mobilenet_v1_1.0_224.txt");
    }

    private MappedByteBuffer loadModelFile(AssetManager assetManager, String MODEL_FILE)
    {
        try
        {
            AssetFileDescriptor fileDescriptor = assetManager.openFd(MODEL_FILE);
            FileInputStream inputStream = new FileInputStream(fileDescriptor.getFileDescriptor());
            FileChannel fileChannel = inputStream.getChannel();
            long startOffset = fileDescriptor.getStartOffset();
            long declaredLength = fileDescriptor.getDeclaredLength();
            return fileChannel.map(FileChannel.MapMode.READ_ONLY, startOffset, declaredLength);
        }
        catch(Exception e)
        {
            Log.e(TAG, "loadModelFile exception");
            e.printStackTrace();
        }
        return null;
    }

    private List<String> loadLabelList(AssetManager assetManager, String labelPath)
    {
        try
        {
            List<String> labelList = new ArrayList<>();
            BufferedReader reader = new BufferedReader(new InputStreamReader(assetManager.open(labelPath)));
            String line;
            while ((line = reader.readLine()) != null)
            {
                labelList.add(line);
            }
            reader.close();
            return labelList;
        }
        catch(Exception e)
        {
            Log.e(TAG, "loadLabelList exception");
            e.printStackTrace();
        }
        return null;
    }

    //SS List<AnomalyClassifierRecognition> recognizeImage(short[] samples)
    public List<AnomalyClassifierRecognition> classify(ByteBuffer samples)
    {
        float[][] result = new float[1][labelList.size()];

        interpreter.run(samples, result);
        //SS Log.d(TAG,"tryRes " + result.length+" "+result[0][0]);
        return getSortedResultFloat(result);
    }

    private List<AnomalyClassifierRecognition> getSortedResultFloat(float[][] labelProbArray)
    {
        Log.d("Classifier", "" + String.format("List Size:(%d, %d, %d)", labelProbArray.length, labelProbArray[0].length, labelList.size()));
        PriorityQueue<AnomalyClassifierRecognition> pq = new PriorityQueue<AnomalyClassifierRecognition>((int) MAX_RESULTS, new Comparator<AnomalyClassifierRecognition>() {
                                                                    @Override
                                                                    public int compare(AnomalyClassifierRecognition lhs, AnomalyClassifierRecognition rhs) {
                                                                        return Float.compare(rhs.confidence, lhs.confidence);
                                                                    }
                                                                });

        for(int i = 0; i < labelList.size(); ++i)
        {
            float confidence = labelProbArray[0][i];
            //SS Log.d(TAG,"confidence " + confidence + " " + labelList.get(i));
            if (confidence > THRESHOLD)
                pq.add(new AnomalyClassifierRecognition(""+ i, labelList.size() > i ? labelList.get(i) : "unknown", confidence));
        }
        final ArrayList<AnomalyClassifierRecognition> recognitions = new ArrayList<>();
        int recognitionsSize = (int) Math.min(pq.size(), MAX_RESULTS);
        for (int i = 0; i < recognitionsSize; ++i) {
            recognitions.add(pq.poll());
        }
        return recognitions;
    }

    public void close()
    {
        if(interpreter != null)
        {
            interpreter.close();
        }
    }
}
