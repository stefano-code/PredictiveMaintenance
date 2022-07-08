//
// Created by ssantilli on 08/07/2022.
//

#include "PCA.h"

#include "debug\Logger.hpp"
#include "os\Thread.hpp"
#include "pca\pca_impl\PCA_Impl.h"


PCA_Impl impl = PCA_Impl();

void PCA::preprocessing(jfloat* samples)
{
    Log.Append("Start preprocessing").EndLine();
    Thread::Sleep(1000);
    Log.Append("End preprocessing").EndLine();
}
//
//void jfloat[] PCA::preprocessing(jshort* samples)
//{
//    Log.Append("Start preprocessing").EndLine();
//    Thread::Sleep(1000);
//    Log.Append("End preprocessing").EndLine();
//}

PCA_Scores PCA::execute(jfloat* samples)
{
    Log.Append("Start executePCA").EndLine();
    Thread::Sleep(1000);
    PCA_Scores scores = PCA_Scores();
    scores.setTSquare(2.2f);
    scores.setSpe(4.2f);
    Log.Append("End executePCA").EndLine();
    return scores;
}
