#include"TGray.h"
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<cstdio>
#include"../common.h"

void TGray(unsigned char *R, unsigned char *G, unsigned char *B, int mode) {
    int gray = 0;
    switch (mode) {
        case 0://mean gray method
            gray = (*R + *G + *B) / 3;
            *R = gray;
            *G = gray;
            *B = gray;
            break;
        case 1://classic gray method
            gray = (299 * *R + 587 * *G + 114 * *B) / 1000;
            *B = gray;
            *G = gray;
            *R = gray;
            break;
        case 2://photoshop gray method
            gray = (MAX2(*B, MAX2(*G, *R)) + MIN2(*B, MIN2(*G, *R))) / 2;
            *B = gray;
            *G = gray;
            *R = gray;
            break;
        default:
            break;
    }
}