/*************************************************************************
Copyright:   Trent.
Author:		 Trent1985
Date:		 2018-9-23
Mail:        dongtingyueh@163.com
Description: Mean Filter
*************************************************************************/
#ifndef __TEST_MEANFILTER__
#define __TEST_MEANFILTER__

#include <jni.h>

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Fast Mean Filter
*Description: Fast Mean Filter process
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*radius: range [0,]
*Return :0-OK,or failed    
************************************************************/
EXPORT int GFastMeanFilter(jint * srcData, int width, int height , int radius);

#else

#ifdef __cplusplus
extern "C" {
#endif   
	int GFastMeanFilter(jint * srcData, int width, int height , int radius);

	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
