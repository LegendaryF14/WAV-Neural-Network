#include <stdio.h>
#include <math.h>
double average_power (int length, float *array)
{
int i=0;
double sum=0;

for (i=0;i<=length;i++)
    sum+=(double)array[i]*(double)array[i];//*array[i];

printf("Average_power sum = %f, using length:%i\n",sum/length,length);
return sum/length;
}

double average_magnitude (int length, float *array)
{
int i=0;
double sum=0;

for(i=0;i<=length;i++)
    sum+=fabs((double)array[i]);

printf("Average_magnitude sum = %f, using length:%i\n",sum/length,length);
return sum/length;
}

double zero_crossings(int length, float *array)
{
int i=0;
double zeros=0;

for(i=0;i<=length;i++)
    if((double)array[i]*(double)array[i+1] < 0)
        zeros++;
printf("Zero_crossing zeros=%f, using length:%i\n",zeros,length);
return zeros;
}

void stats (unsigned int length, float *array, int pos, int start, double *stat)
{
int k=pos-start;
//double stat=0;
printf("\nStarted stats function\n");
if (k==0)
{
    *stat=average_power(length, array);
}

if (k==1)
{
    *stat=average_magnitude(length,array);
}

if (k==2)
{
    *stat=zero_crossings(length,array);
}
printf("Stat=%lf\n",*stat);
//return stat;
}

