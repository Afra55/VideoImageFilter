#include <jni.h>
#include <string>
#include "common.h"


int getPixel(const jint * srcData, int width, int height, int stride, int x, int y, int rgba[3])
{
    x = x < 0 ? 0 : (x > width - 1 ? width - 1 : x);
    y = y < 0 ? 0 : (y > height - 1 ? height - 1 : y);
    int ret = 0;
    //Process
    int pos = x * 4 + y * stride;
    rgba[0] = srcData[pos + 2];
    rgba[1] = srcData[pos + 1];
    rgba[2] = srcData[pos + 0];
    rgba[3] = srcData[pos + 3];
    return ret;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_afra55_filter_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "From C++: 点击选择图片";
    LOGD("JNI 进入成功");
    return env->NewStringUTF(hello.c_str());
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

    jboolean isCopy = JNI_TRUE;
    jint * s = env->GetIntArrayElements(src, &isCopy);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            jint pixel = s[y * width + x];
            uint32_t v = *(uint32_t *)pixel;
            unsigned int a = 0, r = 0, g = 0, b = 0;
            a = (((v) & 0xFF000000) >> 24);
            r = RGBA_R(v);
            g = RGBA_G(v);
            b = RGBA_B(v);
            LOGI("%d %d %d %d", a, r, g, b);
        }
    }
//    jintArray children = env->NewIntArray(width * height);
//    env->SetIntArrayRegion(children, 0, width * height, s);
//    return children;
}