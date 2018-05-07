#include <stdio.h>
#include <stdlib.h>
#include "WAV_Header.h"

void Inputs_Main(float *array, unsigned int length, float *transform, double *sum, double *stat, int network_inputs_length, double *network_array)
{
    //printf("\nStarted Inputs_Main\n");

    //int n=3; //number of inputs to use in neural network
    //struct output network_inputs;
    //network_inputs.length=n;

    //float inputs[n]; //create array to return to neural network

    int i=0; //iterator
    int j=0; //iterator
    int f=0; //frequency iterator
    float *x; //forier transform array placeholder
    int forier_test=0;
    int stats_test=1;

    //printf("\nEstablished variables in Inputs_Main\n");


/*Scanf to determine what functions to run for neural network inputs*/

/*
                                            printf("Would you like to use the forier function as an input for the neural network?(press 1 for yes or 0 for no)?\n");
                                            scanf("%i",&forier_test);

                                            printf("Would you like to use the stats function as an input for the neural network?(press 1 for yes or 0 for no)?\n");
                                            scanf("%i",&stats_test);
*/




/*run selected functions for neural network inputs*/
if (forier_test==1)
{
    for (f=440;f<10000;f*=4)
    {
        forier(length,array,f,transform);
        x=transform;
        integral(length,x,sum);
        //y=*sum;
        network_array[i]=(double)*sum;
        printf("network_array[%i](forier)=%lf\n",i+1, (double)*sum);
        i++;
        j++;
    }
}

if (stats_test==1)
{
    for (;i<network_inputs_length;i++)
    {

        stats(length, array, i, j, stat);
        network_array[i]=(double)*stat;
        printf("Network_array[%i] (stats)= %lf\n",i+1,(double)*stat);
    }
}

    //network_inputs.left=inputs;
/*convert network_inputs struct to network_array point and network_inputs_length to be used in main*/
    //*network_inputs_length=n;
    //network_array=network_inputs.left;

/*Test network_array
    for(j=0;j<network_inputs_length;j++)
    {
        printf("\nInput %i = %f",j+1,network_array[j]);
    }
*/
    //return network_inputs;
}
