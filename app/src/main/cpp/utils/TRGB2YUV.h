#ifndef  __RGB2YUV__
#define  __RGB2YUV__

void RGB2YUV(unsigned char R, unsigned char G, unsigned char B, int *Y, int* U, int*V);
void YUV2RGB(int Y, int U, int V, unsigned char * R, unsigned char * G, unsigned char *B);
#endif