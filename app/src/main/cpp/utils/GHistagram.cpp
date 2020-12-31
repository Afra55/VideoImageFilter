#include"GHistagram.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include <jni.h>
#include"../common.h"

/**
 * 获取直方图数据
 * mode 0: 灰度直方图
 * mode 1: 红色直方图
 * mode 2: 绿度直方图
 * mode 3: 蓝度直方图
 * @param pixelArray
 * @param width
 * @param height
 * @param hist 记录[0..255]像素值对应的的像素个数
 * @param mode
 */
void GHistagram(const jint *pixelArray, int width, int height, int *hist, int mode) {

    int gray;
    switch (mode) {
        case 0://Gray histagram

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = y * width + x;
                    jint pixel = pixelArray[index];
                    unsigned char R = RGBA_R(pixel);
                    unsigned char G = RGBA_G(pixel);
                    unsigned char B = RGBA_B(pixel);
                    gray = (R + G + B) / 3;
                    hist[gray]++;
                }
            }
            break;
        case 1://Red histagram

            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = y * width + x;
                    jint pixel = pixelArray[index];
                    unsigned char R = RGBA_R(pixel);
                    hist[R]++;
                }
            }
            break;
        case 2://Green histagram
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = y * width + x;
                    jint pixel = pixelArray[index];
                    unsigned char G = RGBA_G(pixel);
                    hist[G]++;
                }
            }
            break;
        case 3://Blue histagram
            for (int y = 0; y < height; ++y) {
                for (int x = 0; x < width; ++x) {
                    int index = y * width + x;
                    jint pixel = pixelArray[index];
                    unsigned char B = RGBA_B(pixel);
                    hist[B]++;
                }
            }
            break;
        default:
            break;
    }

}