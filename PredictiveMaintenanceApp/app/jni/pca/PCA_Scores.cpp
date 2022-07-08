//
// Created by ssantilli on 08/07/2022.
//

#include "PCA_Scores.h"

float PCA_Scores::getTSquare()
{
    return t_square;
}

float PCA_Scores::getSpe()
{
    return spe;
}

void PCA_Scores::setTSquare(float v)
{
    t_square = v;
}

void PCA_Scores::setSpe(float v)
{
    spe = v;
}