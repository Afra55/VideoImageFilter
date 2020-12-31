#include"TThreshold.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include"../common.h"
/**
 * 阈值化，大于 T 的都是 255 ，小于T的都是0
 * @param R
 * @param G
 * @param B
 * @param gray
 * @param T
 */
void TThreshold(unsigned char R, unsigned char G, unsigned char B, int *gray, int T)
{
			int temp = (R + G + B) / 3;
			*gray = temp < T ? 0 : 255;
}