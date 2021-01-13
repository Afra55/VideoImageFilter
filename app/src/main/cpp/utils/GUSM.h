/*************************************************************************
Copyright:   Trent.
Author:		 Trent1985
Date:		 2018-9-23
Mail:        dongtingyueh@163.com
Description: USM 
*************************************************************************/
#ifndef __TEST_USM__
#define __TEST_USM__

#include <jni.h>

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  USM
*Description: USM process
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*radius   :Radius of gauss filter, [0,100]
*amount: [0-500]
*threshold:[0,255]
*Return :0-OK,or failed    
************************************************************/
EXPORT int GUSM(jint * srcData, int width, int height, int radius, int amount, int threshold);


#else

#ifdef __cplusplus
extern "C" {
#endif   
	int GUSM(jint * srcData, int width, int height, int radius, int amount, int threshold);

	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
