#ifndef  __RGB2HSI__
#define  __RGB2HSI__

void RGB2HSV(unsigned char R, unsigned char G, unsigned char B, float *H, float *S, float *V);
void HSV2RGB(float H, float S, float V, unsigned char * R, unsigned char * G, unsigned char *B);

#endif