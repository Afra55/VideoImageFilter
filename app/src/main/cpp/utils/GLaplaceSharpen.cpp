#include"GLaplaceSharpen.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include <jni.h>
#include"../common.h"

/**
 * 拉普拉斯锐化
 * @param srcData
 * @param width
 * @param height
 * @param mode 0：4邻域算子， 1：8邻域算子
 * @return
 */
int GLaplaceSharpen(jint *srcData, int width, int height, int mode) {
    int ret = 0;
    jint *tempData = (jint *) malloc(sizeof(jint) * height * width);
    int pos;
    memcpy(tempData, srcData, sizeof(jint) * height * width);
    unsigned char R, G, B, A;
    // 4邻域算子
    if (mode == 0) {
        for (int j = 1; j < height - 1; j++) {
            for (int i = 1; i < width - 1; i++) {
                pos = i + j * width;
                jint pixel = tempData[pos];
                R = RGBA_R(pixel);
                G = RGBA_G(pixel);
                B = RGBA_B(pixel);
                A = RGBA_A(pixel);
                R = CLIP3(R + (R * 4 - RGBA_R(tempData[pos - width]) -
                               RGBA_R(tempData[pos - 1]) - RGBA_R(tempData[pos + 1]) -
                               RGBA_R(tempData[pos + width])), 0, 255);
                G = CLIP3(G + (G * 4 - RGBA_G(tempData[pos - width]) -
                               RGBA_G(tempData[pos - 1]) - RGBA_G(tempData[pos + 1]) -
                               RGBA_G(tempData[pos + width])), 0, 255);
                B = CLIP3(B + (B * 4 - RGBA_B(tempData[pos - width]) -
                               RGBA_B(tempData[pos - 1]) - RGBA_B(tempData[pos + 1]) -
                               RGBA_B(tempData[pos + width])), 0, 255);
                srcData[pos] = MAKE_RGBA(R, G, B, A);
            }
        }
    } else {
        // 8邻域算子
        for (int j = 1; j < height - 1; j++) {
            for (int i = 1; i < width - 1; i++) {
                pos = i + j * width;
                jint pixel = tempData[pos];
                R = RGBA_R(pixel);
                G = RGBA_G(pixel);
                B = RGBA_B(pixel);
                A = RGBA_A(pixel);

                R = CLIP3(R + (R * 8 - RGBA_R(tempData[pos - width]) -
                               RGBA_R(tempData[pos - 1]) -
                               RGBA_R(tempData[pos + 1]) -
                               RGBA_R(tempData[pos + width]) -
                               RGBA_R(tempData[pos - 1 - width]) -
                               RGBA_R(tempData[pos + 1 - width]) -
                               RGBA_R(tempData[pos - 1 + width]) -
                               RGBA_R(tempData[pos + 1 + width])), 0, 255);
                G = CLIP3(G + (G * 8 - RGBA_G(tempData[pos - width]) -
                               RGBA_G(tempData[pos - 1]) -
                               RGBA_G(tempData[pos + 1]) -
                               RGBA_G(tempData[pos + width]) -
                               RGBA_G(tempData[pos - 1 - width]) -
                               RGBA_G(tempData[pos + 1 - width]) -
                               RGBA_G(tempData[pos - 1 + width]) -
                               RGBA_G(tempData[pos + 1 + width])), 0, 255);
                B = CLIP3(B + (B * 8 - RGBA_B(tempData[pos - width]) -
                               RGBA_B(tempData[pos - 1]) -
                               RGBA_B(tempData[pos + 1]) -
                               RGBA_B(tempData[pos + width]) -
                               RGBA_B(tempData[pos - 1 - width]) -
                               RGBA_B(tempData[pos + 1 - width]) -
                               RGBA_B(tempData[pos - 1 + width]) -
                               RGBA_B(tempData[pos + 1 + width])), 0, 255);

                srcData[pos] = MAKE_RGBA(R, G, B, A);
            }
        }
    }
    free(tempData);
    return ret;
};