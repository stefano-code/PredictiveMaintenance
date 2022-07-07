package com.technogym.android.predictivemaintenance.ml;

import android.util.Log;

public class PCA
{
    private static final String TAG = "PCA";

    public native void init();

    public native int checkTemperature(float[] samples);
    public native int checkOrientation(float[] samples);


    public native PCA_Scores execute(float[] samples);

    public PCA()
    {}


    public void onScoresReady(PCA_Scores scores)
    {
        Log.e(TAG, "execute scores " + scores.toString());
    }
    public void onCheckTemperature(int result)
    {
        Log.e(TAG, "check temperature result " + result);
    }
    public void onCheckOrientation(int result)
    {
        Log.e(TAG, "check orientation result " + result);
    }

    static
    {
        System.loadLibrary("pca_native");
    }
}
