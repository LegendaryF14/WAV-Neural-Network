#include <stdio.h>
#include <stdlib.h>
#include "WAV_Header.h"

void wav_1ch_8bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{
    char *mono=malloc(h3.dwChunkSize); // create mono array

    printf("\nCREATED char mono array!\n");

    fread(mono, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in char mono array!!!!\n");

    for(int j=0;j<h3.dwChunkSize;j++)
        {
            left[j]=(float)mono[j];
            if(test==1)
            {
                printf("Sample: %u\t\tLeft(Mono): %f\n",j+1,left[j]); //Visual representation of channels being filled out
            }
        }
}

void wav_1ch_16bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{

    short *mono=malloc(h3.dwChunkSize); // create mono array

    //printf("\nCREATED short mono array!\n");

    fread(mono, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

   // printf("\nFilled in short mono array!!!!\n");

    for(int j=0;j<h3.dwChunkSize/2;j++)
        {
            left[j]=(float)mono[j];
            if(test==1)
            {
                //printf("Sample: %u\t\tLeft(Mono): %f\n",j+1,mono[j]); //Visual representation of channels being filled out
                printf("Sample: %u\t\tLeft(mono): %f\n",j+1,left[j]);
            }
        }
}

void wav_1ch_32bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{
    float *mono=malloc(h3.dwChunkSize); // create mono array

    printf("\nCREATED float mono array!\n");

    fread(mono, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in float mono array!!!!\n");

    for(int j=0;j<h3.dwChunkSize;j++)
        {
            left[j]=(float)mono[j];
            if(test==1)
            {
                printf("Sample: %u\t\tLeft(Mono): %f\n",j+1,mono[j]); //Visual representation of channels being filled out
            }
        }
}



void wav_2ch_8bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{
    int i=0; //wav_array iterator
    int j=0; //channel iterator

    char *wav_array=malloc(h3.dwChunkSize);      // create initial data array
    //left=malloc(h3.dwChunkSize/2);         // create left channel half the size of wav_array
    //right=malloc(h3.dwChunkSize/2);        // create right channel half the size of wav_array

    printf("\nCREATED char wav_array, left, and right arrays!\n");
    fread(wav_array, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in char wav_array!!!\n");
    for (i=0;i<h3.dwChunkSize;i++) //separate wav_array into left and right channel (RIGHT CHANNEL NULL IF MONO)
        {
            left[j]=(float)wav_array[i];
            i++; //next float in wav_array
            right[j]=(float)wav_array[i];

            if (test==1)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
            j++; //next sample in each channel
        }

    printf("FILLED IN LEFT AND RIGHT CHANNEL ARRAYS!!!!");
}

void wav_2ch_16bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{
    int i=0; //wav_array iterator
    int j=0; //channel iterator

    short *wav_array=malloc(h3.dwChunkSize);      // create initial data array
    //left=malloc(h3.dwChunkSize*2);         // create left channel half the size of wav_array
    //right=malloc(h3.dwChunkSize*2);        // create right channel half the size of wav_array

    //printf("\nCREATED short wav_array, left, and right arrays!\n");
    fread(wav_array, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    //printf("\nFilled in short wav_array!!!\n");
    for (i=0;i<(h3.dwChunkSize/2);i++) //separate wav_array into left and right channel (RIGHT CHANNEL NULL IF MONO)
        {
            left[j]=(float)wav_array[i];
            i++; //next float in wav_array
            right[j]=(float)wav_array[i];

            if (test==1)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
            j++; //next sample in each channel
        }

    //printf("FILLED IN LEFT AND RIGHT CHANNEL ARRAYS!!!!");
}

void wav_2ch_32bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{
    int i=0; //wav_array iterator
    int j=0; //channel iterator

    float *wav_array=malloc(h3.dwChunkSize);      // create initial data array
    //left=malloc(h3.dwChunkSize/2);         // create left channel half the size of wav_array
    //right=malloc(h3.dwChunkSize/2);        // create right channel half the size of wav_array

    printf("\nCREATED float wav_array, left, and right arrays!\n");
    fread(wav_array, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in float wav_array!!!\n");
    for (i=0;i<(h3.dwChunkSize/4);i++) //separate wav_array into left and right channel (RIGHT CHANNEL NULL IF MONO)
        {
            left[j]=wav_array[i];
            i++; //next float in wav_array
            right[j]=wav_array[i];

            if (test==1)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
            j++; //next sample in each channel
        }

    printf("FILLED IN LEFT AND RIGHT CHANNEL ARRAYS!!!!");
}
