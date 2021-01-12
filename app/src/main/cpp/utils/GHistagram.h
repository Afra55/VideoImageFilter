#ifndef __TEST_HISTAGRAM__
#define __TEST_HISTAGRAM__

#include <jni.h>

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Histagram
*Description: Compute histagram
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*mode: 0-Gray histagram,1-Red histagram, 2-Green histagram, 3-Blue histagram
*Return :0-OK,or failed    
************************************************************/
EXPORT int GHistagram(const jint *pixelArray, int width, int height, int *hist, int mode);


#else

#ifdef __cplusplus
extern "C" {
#endif   
	void GHistagram(const jint *pixelArray, int width, int height, int *hist, int mode);


	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
