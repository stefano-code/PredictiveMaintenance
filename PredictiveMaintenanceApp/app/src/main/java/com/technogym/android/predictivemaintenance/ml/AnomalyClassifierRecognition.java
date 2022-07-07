package com.technogym.android.predictivemaintenance.ml;

import androidx.annotation.NonNull;

public class AnomalyClassifierRecognition
{
    String id= "";
    String title= "";
    float confidence= 0F;

    public AnomalyClassifierRecognition(String i, String s, float confidence) {
        id= i;
        title = s;
        this.confidence = confidence;
    }

    @NonNull
    @Override
    public String toString() {
        return "Title = "+title+", Confidence = "+confidence + ", id" + id;
    }
}
