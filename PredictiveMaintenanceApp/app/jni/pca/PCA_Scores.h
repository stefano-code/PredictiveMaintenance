//
// Created by ssantilli on 08/07/2022.
//

#ifndef PREDICTIVEMAINTENANCEAPP_PCA_SCORES_H
#define PREDICTIVEMAINTENANCEAPP_PCA_SCORES_H


class PCA_Scores {
private:
    float t_square;
    float spe;
public :
    float getTSquare();
    float getSpe();
    void setTSquare(float v);
    void setSpe(float v);
};


#endif //PREDICTIVEMAINTENANCEAPP_PCA_SCORES_H
