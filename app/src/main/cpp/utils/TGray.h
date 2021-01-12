#ifndef __TEST_GRAY__
#define __TEST_GRAY__

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Gray
*Description: Color image convert to gray image.
*Params:    
*srcData:  image bgra data     
*width  :image width
*height :image height
*stride :image stride
*mode: 0-mean gray,1-classic gray, 2-ps gray
*Return :0-OK,or failed    
************************************************************/
EXPORT int TGray(unsigned char * R, unsigned char * G, unsigned char *B, int mode);


#else

#ifdef __cplusplus
extern "C" {
#endif
	void TGray(unsigned char * R, unsigned char * G, unsigned char *B, int mode);

	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
