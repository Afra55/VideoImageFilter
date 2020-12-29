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
            int red = RGBA_R(pixel);  //获取红色灰度值
            int green = RGBA_G(pixel); //获取绿色灰度值
            int blue = RGBA_B(pixel);         //获取蓝色灰度值
            int alpha = RGBA_A(pixel);         //获取蓝色灰度值
            pixel = (int) ((float) red * 0.3 + (float) green * 0.59 + (float) blue * 0.11);
            pixel = 0xFF << 24 | (pixel << 16) | (pixel << 8) | pixel; //添加透明度
            s[y * width + x] = pixel;
        }
    }
}