package com.technogym.android.predictivemaintenance.ml;

import androidx.annotation.NonNull;

public class PCA_Scores
{
    private float t_square;
    private float spe;  // square prediction error

    public PCA_Scores()
    {}

    public float getTSquare()
    {
        return t_square;
    }

    public float getSpe()
    {
        return spe;
    }

    @NonNull
    @Override
    public String toString()
    {
        return String.format("t_square: %f  spe : %f", t_square, spe);
    }
}
