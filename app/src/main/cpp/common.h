#ifndef VIDEOIMAGEFILTER_COMMON_H
#define VIDEOIMAGEFILTER_COMMON_H

#include <android/log.h>
#include <stdint.h>
#include <sys/types.h>

#define TAG        "VideoImageFilter"
#define LOGW(...)    __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(...)    __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#define LOGI(...)    __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGD(...)    __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define RGBA_A(p) (((p) & 0xFF000000) >> 24)  // 0, 255
#define RGBA_R(p) (((p) & 0x00FF0000) >> 16)  // 0 - 255
#define RGBA_G(p) (((p) & 0x0000FF00) >>  8)  // 0 - 255
#define RGBA_B(p)  ((p) & 0x000000FF)  // 0 - 255
#define MAKE_RGBA(r,g,b,a) (((a) << 24) | ((r) << 16) | ((g) << 8) | (b))

#define MIN2(a, b) ((a) < (b) ? (a) : (b))
#define MAX2(a, b) ((a) > (b) ? (a) : (b))
#define CLIP3(x, a, b) MIN2(MAX2(a,x), b)
typedef unsigned short Char16;
typedef unsigned int Char32;
#endif
