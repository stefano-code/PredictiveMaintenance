
#ifndef PREDICTIVEMAINTENANCEAPP_PCA_H
#define PREDICTIVEMAINTENANCEAPP_PCA_H

#include <jni.h>
#include "pca\PCA_Scores.h"

class PCA {

public:
    void preprocessing(jfloat* samples);
    PCA_Scores execute(jfloat* samples);
};

#endif //PREDICTIVEMAINTENANCEAPP_PCA_H
