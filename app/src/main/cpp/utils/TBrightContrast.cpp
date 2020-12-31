#include"TBrightContrast.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include"../common.h"

/**
 * 亮度对比度调节
 * @param pixelArray
 * @param width
 * @param height
 * @param bright 亮度
 * @param contrast  对比度
 */
void TBrightContrast(jint *pixelArray, int width, int height, int bright, int contrast)
{
	bright = CLIP3(bright,-100,100);
	contrast = CLIP3(contrast, -100,100);
	//compute average light of image
	int Average = 0;

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			jint pixel = pixelArray[index];
			unsigned char R = RGBA_R(pixel);
			unsigned char G = RGBA_G(pixel);
			unsigned char B = RGBA_B(pixel);

			// 灰度化公式
			Average += (299 *  R + 587 * G + 114 * B) / 1000;
		}
	}
	// 灰度均值
	Average = Average / (width * height);
	unsigned char BC_MAP[256];
	int temp =0;
	for(int i = 0; i < 256; i++)
	{
		temp = contrast > 0 ? CLIP3(i + bright, 0, 255) : i;
		if(contrast > 0)
		{
			temp = CLIP3(i + bright, 0, 255);
			temp = CLIP3(Average + (temp - Average) * (1.0f / (1.0f - contrast / 100.0f)), 0, 255);
		}
		else
		{
			temp = i;
			temp = CLIP3(Average + (temp - Average) * (1.0f + contrast / 100.0f), 0, 255);
			temp = CLIP3(temp + bright, 0, 255);
		}
		BC_MAP[i] = temp;
	}

	for (int y = 0; y < height; ++y) {
		for (int x = 0; x < width; ++x) {
			int index = y * width + x;
			jint pixel = pixelArray[index];
			unsigned char R = RGBA_R(pixel);
			unsigned char G = RGBA_G(pixel);
			unsigned char B = RGBA_B(pixel);
			unsigned char A = RGBA_A(pixel);
			R = BC_MAP[R];
			G = BC_MAP[G];
			B = BC_MAP[B];
			pixelArray[index] = MAKE_RGBA(R, G, B, A);
		}
	}
}

