#include"GGaussFilter.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include <jni.h>
#include"../common.h"
/*************************************************************
*Function: 高斯模版计算
*Params:
*      r-radius of gauss filter
*      sigma-sigma of gauss filter
*      gaussMask-gauss weight to compute with size of (2r+1)*(2r+1)
*Return NULL
************************************************************/
void GaussMask(int r, double sigma, double gaussMask[])
{
	double PI = 3.1415926;
	double sum = 0;
	int stride = 2 * r + 1;
    for (int y = -r, h = 0; y <= r; y++, h++)
    {
        for (int x = -r, w = 0; x <= r; x++, w++)
        {
            gaussMask[w + h * stride] = (1.0 / (2.0 * PI * sigma * sigma)) * (exp(-((double)x * (double)x + (double)y * (double)y) / (2.0 * sigma * sigma)));
			sum += gaussMask[w + h * stride];
        }
    }
	for (int i = 0; i < stride * stride; i++)
    {
        gaussMask[i] = gaussMask[i] / sum;
    }
}
/**
 * 高斯滤波, 先对图像按行进行一次一维高斯滤波，再对结果图像按列进行一次一维高斯滤波。而两次高斯滤波，在相同半径的情况下，高斯计算得到的权重值是相同的，避免了重复计算，因此，速度将大大加快。
 * @param srcData
 * @param width
 * @param height
 * @param r 高斯滤波半径
 * @return
 */
int GFastGaussFilter(jint *srcData, int width, int height, float r)
{
	int ret = 0;
	int radius = (int)r;
	if(r == 0)
		return ret;
    jint* dstData = (jint*)malloc(sizeof(jint) * height * width);
    jint* tempData = (jint*)malloc(sizeof(jint) * height * width);
	memset(dstData, 255, sizeof(jint) * height * width);
    int totalWei = 0;
    int i,j,k;
    float sigma = r;   
    unsigned char *kernel = (unsigned char *)malloc(2*radius+1);
    for (i = -radius; i <= radius; i++)
    {        
        kernel[i+radius] = (unsigned char) (exp(-(float)i*i/(2*sigma*sigma))*128);
        totalWei += kernel[i+radius];
    }
    int tempR = 0, tempG = 0, tempB = 0;
    int v = 0;
    int K = 0;
    int rem = 0;
    int t = 0;
    for ( j = 0; j < height; j++)
    {
        for ( i = 0; i < width; i++)
        {
            tempR = 0; tempG = 0; tempB = 0;
            for ( k = -radius; k <= radius; k++)
            {
                rem = (abs(i + k) % width);
                t = rem  + j * width;
                K = kernel[k + radius];
                jint pixel = srcData[t];
                unsigned char R = RGBA_R(pixel);
                unsigned char G = RGBA_G(pixel);
                unsigned char B = RGBA_B(pixel);
                tempB += B * K;
                tempG += G * K;
                tempR += R * K;
            }
            v = i  + j * width;
            unsigned char A = RGBA_A(srcData[v]);
            tempData[v] = MAKE_RGBA(tempR / totalWei, tempG / totalWei, tempB / totalWei, A);
        }
    }
    for ( i = 0; i < width; i++)
    {
        for ( j = 0; j < height; j++)
        {
            tempR = 0; tempG = 0; tempB = 0;
            for ( k = -radius; k <= radius; k++)
            {
                rem = (abs(j + k) % height);
                t = rem * width + i ;
                K = kernel[k + radius];
                jint pixel = tempData[t];
                unsigned char R = RGBA_R(pixel);
                unsigned char G = RGBA_G(pixel);
                unsigned char B = RGBA_B(pixel);
                tempB += B * K;
                tempG += G * K;
                tempR += R * K;
            }
            v = i + j * width;
            unsigned char A = RGBA_A(srcData[v]);
            dstData[v] = MAKE_RGBA(tempR / totalWei, tempG / totalWei, tempB / totalWei, A);
        }
    }
	memcpy(srcData, dstData, sizeof(jint) * height * width);
	free(dstData);
    free(tempData);
    return ret;
};