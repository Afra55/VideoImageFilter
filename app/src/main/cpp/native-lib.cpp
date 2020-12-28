#include <jni.h>
#include <string>

extern "C" JNIEXPORT jstring JNICALL
Java_com_afra55_filter_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "From C++: 点击选择图片";
    return env->NewStringUTF(hello.c_str());
}