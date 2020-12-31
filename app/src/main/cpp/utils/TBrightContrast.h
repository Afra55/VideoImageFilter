#ifndef __TEST_BRIGHT_CONTRAST__
#define __TEST_BRIGHT_CONTRAST__

#include <jni.h>

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Bright&contrast adjust
*Description: Bright and contrast adjust process
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*bright: range [-100,100]
*contrast: range [-100,100]
*Return :0-OK,or failed    
************************************************************/
EXPORT int f_BrightContrast(unsigned char *srcData, int width, int height, int stride, int bright, int contrast);


#else

#ifdef __cplusplus
extern "C" {
#endif   
	void TBrightContrast(jint *pixelArray, int width, int height, int bright, int contrast);


	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
