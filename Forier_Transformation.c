#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define PI 3.14153

void forier(unsigned int T, float *array, int f, float *c)
{
    //printf("\nStarted forier function\n");

    float *a=malloc(4*T);
    float *b=malloc(4*T);

    //printf("\nEstablished arrays in forier function\n");

    int i=0;

    for(i=0;i<T;i++)
    {
        a[i]=array[i]*cos(2*3.14*f*i/T);
        b[i]=array[i]*sin(2*PI*f*i/T);
        c[i]=sqrt((a[i]*a[i]+b[i]*b[i]));
    }
    //printf("\nMade it to end of forier function\n");

}
