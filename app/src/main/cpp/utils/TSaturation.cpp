#include"TSaturation.h"
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdio.h>
#include"../common.h"

/**
 * 饱和度调整
 * @param R
 * @param G
 * @param B
 * @param saturation 饱和度 [-100..100]
 */
void TSaturation(unsigned char *R, unsigned char *G, unsigned char *B, int saturation) {
    int rgbMin, rgbMax;
    saturation = CLIP3(saturation, -100, 100);
    int k = saturation / 100.0f * 128;
    int alpha = 0;
    rgbMin = MIN2(MIN2(*R, *G), *B);
    rgbMax = MAX2(MAX2(*R, *G), *B);
    int delta = (rgbMax - rgbMin);
    int value = (rgbMax + rgbMin);
    if (delta != 0) {
        int L = value >> 1;
        int S = L < 128 ? (delta << 7) / value : (delta << 7) / (510 - value);
        if (k >= 0) {
            alpha = k + S >= 128 ? S : 128 - k;
            alpha = 128 * 128 / alpha - 128;
        } else
            alpha = k;
        *R = CLIP3(*R + ((*R - L) * alpha >> 7), 0, 255);
        *G = CLIP3(*G + ((*G - L) * alpha >> 7), 0, 255);
        *B = CLIP3(*B + ((*B - L) * alpha >> 7), 0, 255);
    }
}

