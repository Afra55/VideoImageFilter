#include"GMeanFilter.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include <jni.h>
#include"../common.h"

//快速均值滤波，模拟到第三行就能理解为什么这样写了，舍弃边缘的精准计算（边缘可以忽略）来实现的算法
int GFastMeanFilter(jint *srcData, int width, int height,  int radius) {
    int ret = 0;
    if (radius == 0)
        return ret;
    // 约束中值滤波的半径
    if (radius > MIN2(width, height) / 2)
        radius = (MIN2(width, height) / 2 - 0.5);
    jint* dstData = (jint*)malloc(sizeof(jint) * height * width);
    memset(dstData, 255, sizeof(jint) * height * width);
    int t = 0, t1 = 0;
    int i,j,k,len = width * height;
    // 计算区域的宽
    int block = (radius << 1) + 1;
    // 计算区域的像素个数
    int winSize = block * block;
    // RGB 色素各自的总值
    long sumB = 0, sumG = 0, sumR = 0;
    jint * pSrc = srcData;
    // 存储BGRA的值
    jint* tempB = (jint*)malloc(sizeof(jint) * width);
    memset(tempB, 0, sizeof(jint ) * width);
    jint* tempG = (jint*)malloc(sizeof(jint) * width);
    memset(tempG, 0, sizeof(jint ) * width);
    jint* tempR = (jint*)malloc(sizeof(jint) * width);
    memset(tempR, 0, sizeof(jint ) * width);
    for (k = -radius; k <= radius; ++k) {
        for (j = 0; j < width; ++j) {
            t = j;
            t1 = abs(k) * width;
            jint pixel = pSrc[t + t1];
            unsigned char R = RGBA_R(pixel);
            unsigned char G = RGBA_G(pixel);
            unsigned char B = RGBA_B(pixel);
            tempB[t] += B;
            tempR[t] += R;
            tempG[t] += G;
        }
    }
    for (i = 0; i < height; ++i) {
        sumB = sumG = sumR = 0;
        for (j = -radius; j <= radius ; ++j) {
            t = abs(j);
            sumB += tempB[t];
            sumR += tempR[t];
            sumG += tempG[t];
        }
        for (j = 0; j < width; ++j) {
            t = j + i * width;
            unsigned char A = RGBA_A(pSrc[t]);
            dstData[t] = MAKE_RGBA((sumR / winSize), (sumG / winSize), (sumB / winSize), A);
            if (j < width - 1) {
                t = abs(j - radius);
                t1 = (j + radius + 1) % width;
                sumB = sumB - tempB[t] + tempB[t1];
                sumG = sumG - tempG[t] + tempG[t1];
                sumR = sumR - tempR[t] + tempR[t1];
            }
        }
        if (i < height - 1) {
            for (k = 0; k < width; ++k) {
                t = k + abs(i - radius) * width;
                t1 = k + (i + radius + 1) % height * width;
                jint top_pixel = pSrc[t];
                jint bottom_pixel = pSrc[t1];
                tempB[k] = tempB[k] - RGBA_B(top_pixel) + RGBA_B(bottom_pixel);
                tempG[k] = tempG[k] - RGBA_G(top_pixel) + RGBA_G(bottom_pixel);
                tempR[k] = tempR[k] - RGBA_R(top_pixel) + RGBA_R(bottom_pixel);
            }
        }
    }

    memcpy(srcData, dstData, sizeof(jint) * height * width);
    free(dstData);
    free(tempR);
    free(tempG);
    free(tempB);
    return ret;
};
