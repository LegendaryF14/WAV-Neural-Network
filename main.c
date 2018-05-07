#include <stdio.h>
#include <stdlib.h>
#include "WAV_Header.h"
#define OUTFILE "one.txt"


/*CURRENTLY SET FOR 3 INPUTS, USING STATS ONLY, WRITING TO FILE "one.txt" */

/* SOME TESTING PARAMETERS ARE COMMENTED OUT IN WAV_Process.c, Network_Inputs_Main.c, and main.c */



int main ()
{
/*Primary Array Pointers*/
float *left;
float *right;
float *transform; //Array pionter for "forier" output
unsigned int length; //Length of (left) array used for running loops through the array
/*Pointer for integral*/
double sum=0;
double *sum_ptr=&sum;
/*Pointer for stats */
double stat=0;
double *stat_ptr=&stat;
/*Network Input Variables*/

//ADJUST NETWORK_LENGTH TO PROPER NUMBER OF INPUTS FOR NEURAL NETWORK

int network_length=3; //length of network_inputs array



/*
        printf("How many inputs would you like to put into the neural network?\n");
        scanf("%i",&network_length);
*/
double network_inputs[network_length]; //array of inputs to be used in the neural network




struct header h1;
struct format h2;
struct data h3;

//OPEN A FILE BASED ON FILENAME INPUT
char input[255];
printf("Please enter the filename of the WAV file you would like to process\n(Please be sure the file is in the same folder as this codea and there are no spaces in filenames)\n\nFILENAME: ");
scanf("%s", input);
FILE *myfile = fopen(input, "rb");
FILE *outfile = fopen(OUTFILE, "a");

if(myfile==NULL)
{
    printf("Error: no file\n");
}

else
{
    fread(&h1, sizeof(struct header), 1, myfile);   // WAV File Header Chunk    - Fills in h1
    fread(&h2, sizeof(struct format), 1, myfile);   // WAV File Format Chunk    - Fills in h2
    fread(&h3, sizeof(struct data), 1, myfile);     // WAV File Data Chunk      - Fills in h3
/*allocate memory and array length for rest of functions, based on file format*/
    if (h2.wChannels==1)
    {
        if (h2.dwBitsPerSample==8)
        {
            left=malloc(h3.dwChunkSize*4);
            //right=malloc(h3.dwChunkSize*4);
            length=h3.dwChunkSize;
        }
        if (h2.dwBitsPerSample==16)
        {
            left=malloc(h3.dwChunkSize*2);
            //right=malloc(h3.dwChunkSize*2);
            length=h3.dwChunkSize/2;
        }
        if (h2.dwBitsPerSample==32)
        {
            left=malloc(h3.dwChunkSize);
            //right=malloc(h3.dwChunkSize*2);
            length=h3.dwChunkSize/4;
        }
    }

    if (h2.wChannels==2)
    {
        if (h2.dwBitsPerSample==8)
        {
            left=malloc(h3.dwChunkSize*2);
            right=malloc(h3.dwChunkSize*2);
            length=h3.dwChunkSize/2;
        }

        if (h2.dwBitsPerSample==16)
        {
            left=malloc(h3.dwChunkSize);
            right=malloc(h3.dwChunkSize);
            length=h3.dwChunkSize/4;
        }

        if (h2.dwBitsPerSample==32)
        {
            left=malloc(h3.dwChunkSize/2);
            right=malloc(h3.dwChunkSize/2);
            length=h3.dwChunkSize/8;
        }
    }
    transform=malloc(4*length);




            wav_print(h1,h2,h3); //Print WAV File Header Info




    /* wav_process passes inputs to WAV_Arrays.c, which fill in array pointers 09 */
    wav_process(h1,h2,h3,myfile,left,right); //Send header structs, file, and channel array pointers to be allocated to proper function to be filled in

    //printf("\nMADE IT PAST WAV_PROCESS\n");




//            end_test(h1,h2,h3,left,right); //Run WAV_Test.c to test final channel arrays created


printf("\nLength of Array(left) = %u\n", length);

Inputs_Main(left, length, transform, sum_ptr, stat_ptr, network_length, network_inputs);

for(int j=0;j<network_length;j++)
    {
        printf("\nInput %i = %lf",j+1,network_inputs[j]);
    }
printf("\n\nLength of network_input array = %i\n", network_length);

//fprintf(outfile, "\n%lf\t%lf\t%lf", network_inputs[0], network_inputs[1], network_inputs[2]);
}

/*
POSSIBLE WAY TO CREATE ERROR MESSAGE IF CODE FAILS TO CREATE ARRAY, LOOK UP IN TEXT BOOK
switch (x);
case (h2.)
default
{
    printf("\nERROR: Unable to create wav_array");
}
*/
free(left);
free(right);
fclose(myfile);
fclose(outfile);

    return 0;
}
