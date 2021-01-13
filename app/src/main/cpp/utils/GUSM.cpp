#include"GUSM.h"
#include"GGaussFilter.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include"../common.h"

/**
 * UMS 锐化
 * @param srcData
 * @param width
 * @param height
 * @param radius 半径 [0..100]
 * @param amount 数量 [0..500]
 * @param threshold 阈值 [0..255]
 * @return
 */
int GUSM(jint * srcData, int width, int height, int radius, int amount, int threshold)
{
	int ret = 0;
    if(radius == 0)
		return ret;
	radius = CLIP3(radius, 0, 100);
	amount = CLIP3(amount, 0,500);
	threshold = CLIP3(threshold, 0,255);
	jint* gaussData = (jint*)malloc(sizeof(jint) * width * height);
	memcpy(gaussData, srcData, sizeof(jint) * width * height);
	GFastGaussFilter(gaussData, width, height, radius);
	int i, j, t;
	unsigned char r, g, b, a;
	amount = amount * 128 / 100;
	jint* pSrc = srcData;
	jint* pDst = gaussData;
	jint* maskData = (jint*)malloc(sizeof(jint) * width * height);
	jint* pMask = maskData;
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			t = j * width + i ;
			r = abs(RGBA_R(pSrc[t]) - RGBA_R(pDst[t])) < threshold ? 0 : 128;
			g = abs(RGBA_G(pSrc[t]) - RGBA_G(pDst[t])) < threshold ? 0 : 128;
			b = abs(RGBA_B(pSrc[t]) - RGBA_B(pDst[t])) < threshold ? 0 : 128;
			a = RGBA_A(pSrc[t]);
			pMask[t] = MAKE_RGBA(r, g, b, a);
		}
	}
	pDst = gaussData;
	pSrc = srcData;
	pMask = maskData;
	GFastGaussFilter(maskData, width, height, radius);
	for(j = 0; j < height; j++)
	{
		for(i = 0; i < width; i++)
		{
			t = j * width + i ;
			jint srcB = RGBA_B(pSrc[t]);
			jint srcG = RGBA_G(pSrc[t]);
			jint srcR = RGBA_R(pSrc[t]);

			b = srcB - RGBA_B(pDst[t]);
			g = srcG - RGBA_G(pDst[t]);
			r = srcR - RGBA_R(pDst[t]);

			b = (srcB + ((b * amount) >> 7));
			g = (srcG + ((g * amount) >> 7));
			r = (srcR + ((r * amount) >> 7));

			jint maskB = RGBA_B(pMask[t]);
			jint maskR = RGBA_R(pMask[t]);
			jint maskG = RGBA_G(pMask[t]);

			b = (b * maskB + srcB * (128 - maskB)) >> 7;
			g = (g * maskG + srcG * (128 - maskG)) >> 7;
			r = (r * maskR + srcR * (128 - maskR)) >> 7;

			b = CLIP3(b, 0, 255);
			g = CLIP3(g, 0, 255);
			r = CLIP3(r, 0, 255);

			pSrc[t] = MAKE_RGBA(r, g, b, RGBA_A(pSrc[t]));
		}
	}
	free(gaussData);
	free(maskData);
	return ret;
};
