#ifndef __TEST_SATURATION__
#define __TEST_SATURATION__

#ifdef _MSC_VER

#ifdef __cplusplus
#define EXPORT extern "C" _declspec(dllexport)
#else
#define EXPORT __declspec(dllexport)
#endif

/************************************************************
*Function:  Saturation adjust
*Description: Saturation process
*Params:    
*srcData:  image bgr data     
*width  :image width
*height :image height
*stride :image stride
*saturation: range [-100,100]
*Return :0-OK,or failed    
************************************************************/
EXPORT void TSaturation(unsigned char *R, unsigned char *G, unsigned char *B, int saturation);


#else

#ifdef __cplusplus
extern "C" {
#endif   
	void TSaturation(unsigned char *R, unsigned char *G, unsigned char *B, int saturation);


	////
	#ifdef __cplusplus
}
#endif


#endif
#endif
