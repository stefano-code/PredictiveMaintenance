#include <jni.h>
#include "debug\Logger.hpp"
#include "os\Thread.hpp"


static JavaVM* gVm = NULL;
static jobject gObj = NULL;
static jmethodID onScoresReady = NULL;
static jmethodID onCheckTemperature = NULL;
static jmethodID onCheckOrientation = NULL;

typedef struct{
    float t_square;
    float spe;
}Scores;

void preprocessing(jfloat*);
Scores executePCA(jfloat*);
jint checkTemperature(jfloat*);
jint checkOrientation(jfloat*);

extern "C" JNIEXPORT void JNICALL Java_com_technogym_android_predictivemaintenance_ml_PCA_init(JNIEnv *env, jobject thiz)
{
    Log.Append("EXECUTE PCA").EndLine();

    if (NULL == gObj)
        gObj = env->NewGlobalRef(thiz);

    if (NULL == onScoresReady) {
        jclass clazz = env->GetObjectClass(thiz);
        onScoresReady = env->GetMethodID(clazz, "onScoresReady",
                                         "(Lcom/technogym/android/predictivemaintenance/ml/PCA_Scores;)V");
    }

    if (NULL == onCheckTemperature) {
        jclass clazz = env->GetObjectClass(thiz);
        onCheckTemperature = env->GetMethodID(clazz, "onCheckTemperature","(I)V");
    }

    if (NULL == onCheckOrientation) {
        jclass clazz = env->GetObjectClass(thiz);
        onCheckOrientation = env->GetMethodID(clazz, "onCheckOrientation","(I)V");
    }
}

extern "C" JNIEXPORT jint JNICALL Java_com_technogym_android_predictivemaintenance_ml_PCA_checkTemperature(JNIEnv *env, jobject thiz, jfloatArray _samples) {
    Log.Append("EXECUTE CHECKTEMPERATURE").EndLine();

    jboolean isCopy = true;
    jsize size = (*env).GetArrayLength(_samples);
    Log.Append("samples size %d", size).EndLine();
    jfloat* samples = (*env).GetFloatArrayElements(  _samples, &isCopy);

    jint res = checkTemperature(samples);

    (*env).ReleaseFloatArrayElements(_samples, samples, 0);

    if(NULL != gObj && NULL != onCheckTemperature)
        (*env).CallVoidMethod(gObj, onCheckTemperature, res);

    return res;
}

extern "C" JNIEXPORT jint JNICALL Java_com_technogym_android_predictivemaintenance_ml_PCA_checkOrientation(JNIEnv *env, jobject thiz, jfloatArray _samples)
{
    Log.Append("EXECUTE CHECKORIENTATION").EndLine();

    jboolean isCopy = true;
    jsize size = (*env).GetArrayLength(_samples);
    Log.Append("samples size %d", size).EndLine();
    jfloat* samples = (*env).GetFloatArrayElements(  _samples, &isCopy);

    jint res = checkOrientation(samples);

    (*env).ReleaseFloatArrayElements(_samples, samples, 0);

    if(NULL != gObj && NULL != onCheckOrientation)
        (*env).CallVoidMethod(gObj, onCheckOrientation, res);

    return res;
}

extern "C" JNIEXPORT jobject JNICALL Java_com_technogym_android_predictivemaintenance_ml_PCA_execute(JNIEnv *env, jobject thiz, jfloatArray _samples) {
    Log.Append("EXECUTE PCA").EndLine();

//    if(NULL == gObj)
//        gObj = env->NewGlobalRef(thiz);
//
//    if(NULL == onScoresReady)
//    {
//        jclass clazz = env->GetObjectClass(thiz);
//        onScoresReady = env-> GetMethodID(clazz, "onScoresReady", "(Lcom/technogym/android/predictivemaintenance/ml/PCA_Scores;)V");
//    }

    jboolean isCopy = true;
    jsize size = (*env).GetArrayLength(_samples);
    Log.Append("samples size %d", size).EndLine();
    jfloat* samples = (*env).GetFloatArrayElements(  _samples, &isCopy);
    for(int i = 0; i < 10 ; i++)
        Log.Append("PCA sample %d", i).Append(" value %f", samples[i]).EndLine();
    for(int i = size-1; i > size-10 ; i--)
        Log.Append("PCA sample %d", i).Append(" value %f", samples[i]).EndLine();


    preprocessing(samples);
    Scores scores = executePCA(samples);


    (*env).ReleaseFloatArrayElements(_samples, samples, 0);

    jclass pca_scores_class = (*env).FindClass("com/technogym/android/predictivemaintenance/ml/PCA_Scores");
    jmethodID pca_scores_constructor = (*env).GetMethodID(pca_scores_class, "<init>", "()V");
    jobject pca_scores_instance = (*env).NewObject(pca_scores_class, pca_scores_constructor);
    jfieldID t_square_field = (*env).GetFieldID(pca_scores_class, "t_square", "F");
    jfieldID spe_field = (*env).GetFieldID(pca_scores_class, "spe", "F");
    (*env).SetFloatField(pca_scores_instance , t_square_field, scores.t_square);
    (*env).SetFloatField(pca_scores_instance , spe_field, scores.spe);

    if(NULL != gObj && NULL != onScoresReady)
        (*env).CallVoidMethod(gObj, onScoresReady, pca_scores_instance);

    return pca_scores_instance;
}

jint checkTemperature(jfloat* samples)
{
    Log.Append("Start checkTemperature").EndLine();
    Thread::Sleep(500);
    Log.Append("End checkTemperature").EndLine();
    return 1;
}
jint checkOrientation(jfloat* samples)
{
    Log.Append("Start checkOrientation").EndLine();
    Thread::Sleep(500);
    Log.Append("End checkOrientation").EndLine();
    return 0;
}

void preprocessing(jfloat* samples)
{
    Log.Append("Start preprocessing").EndLine();
    Thread::Sleep(1000);
    Log.Append("End preprocessing").EndLine();
}

Scores executePCA(jfloat* samples)
{
    Log.Append("Start executePCA").EndLine();
    Thread::Sleep(1000);
    Scores scores;
    scores.t_square = 2.2f;
    scores.spe = 4.2f;
    Log.Append("End executePCA").EndLine();
    return scores;
}
