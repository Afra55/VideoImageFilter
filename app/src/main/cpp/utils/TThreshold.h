/*************************************************************************
Copyright:   Trent.
Author:		 Trent1985
Date:		 2018-9-23
Mail:        dongtingyueh@163.com
Description: Threshold
*************************************************************************/
#ifndef __TEST_THRESHOLD__
#define __TEST_THRESHOLD__

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Threshold
*Description: Color image convert to threshold image.
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*T: threshold, range [0,255]
*Return :0-OK,or failed    
************************************************************/
EXPORT void TThreshold(unsigned char R, unsigned char G, unsigned char B, int *gray, int T);


#else

#ifdef __cplusplus
extern "C" {
#endif   
	void TThreshold(unsigned char R, unsigned char G, unsigned char B, int *gray, int T);


	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
