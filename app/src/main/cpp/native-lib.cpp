#include <jni.h>
#include <string>
#include "common.h"
#include "utils/TRGB2HSV.h"
#include "utils/TRGB2YUV.h"
#include "utils/TRGB2LAB.h"
#include "utils/TGray.h"


jint makeGray(jint pixel, int red, int green, int blue);

void HSVAdjust(float hIntensity, float sIntensity, float vIntensity, unsigned char &R, unsigned char &G, unsigned char &B);

extern "C" JNIEXPORT jstring JNICALL
Java_com_afra55_filter_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "From C++: 点击选择图片";
    LOGD("JNI 进入成功");
    return env->NewStringUTF(hello.c_str());
}

/**
 * HSV 调节
 * @param hIntensity
 * @param sIntensity
 * @param vIntensity
 * @param R
 * @param G
 * @param B
 */
void HSVAdjust(float hIntensity, float sIntensity, float vIntensity, unsigned char &R, unsigned char &G, unsigned char &B) {
    float h = 0, s = 0, v = 0;
    RGB2HSV(R, G, B, &h, &s, &v);
    h = h + hIntensity > 360 ? h + hIntensity - 360 : h + hIntensity;
    s = CLIP3(s + sIntensity, 0, 1.0f);
    v = CLIP3(v + vIntensity, 0, 1.0f);
    HSV2RGB(h, s, v, &R, &G, &B);
}


extern "C" JNIEXPORT void JNICALL
Java_com_afra55_filter_MainActivity_bitmapLogicFromJNI(
        JNIEnv *env,
        jobject,
        jintArray src,
        int width,
        int height,
        int stride
) {

    jboolean isCopy = JNI_FALSE;
    jint * pixelArray = env->GetIntArrayElements(src, &isCopy);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int index = y * width + x;
            jint pixel = pixelArray[index];
            unsigned char R = RGBA_R(pixel);  //获取红色灰度值
            unsigned char G = RGBA_G(pixel); //获取绿色灰度值
            unsigned char B = RGBA_B(pixel);         //获取蓝色灰度值
            unsigned char A = RGBA_A(pixel);         //获取蓝色灰度值
            TGray( &R, &G, &B, 2);
            pixelArray[index] = MAKE_RGBA(R, G, B, A);
        }
    }
}

