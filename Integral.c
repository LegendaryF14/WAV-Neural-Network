#include <stdio.h>

void integral(int length, float *array, double *sum)
{
    //printf("\nStarted Integral Function\n");
    //float sum=0;
    double area=0;
    *sum=0;

    for(int i=0;i<=length;i++)
    {
        area=(((double)array[i]+(double)array[i+1])/2);
        //printf("tylers_array[%i]; sum=%f\n",i+1, sum);
        *sum+=area;
    }
    printf("\nSum=%lf\n",*sum);

    //return sum;
}
