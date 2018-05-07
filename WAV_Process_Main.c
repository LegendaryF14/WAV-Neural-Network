//Tyler Kupczak
//WAV file processing using binary




//THIS CODE FILE MAY BE UNNECESSARY




















#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "WAV_Header.h"
/*
unsigned int WAV_Main(float *left, float *right)
{

struct header h1;
struct format h2;
struct data h3;
unsigned int length;
//float *left;
//float *right;


//OPEN A FILE BASED ON FILENAME INPUT
char input[255];

printf("Please enter the filename of the WAV file you would like to process\n(Please be sure the file is in the same folder as this codea and there are no spaces in filenames)\n\nFILENAME: ");
scanf("%s", input);

FILE *myfile = fopen(input, "rb");
    if(myfile==NULL)
    {
        printf("Error: no file\n");
    }
    else
    {
    fread(&h1, sizeof(struct header), 1, myfile);   // WAV File Header Chunk
    fread(&h2, sizeof(struct format), 1, myfile);   // WAV File Format Chunk
    fread(&h3, sizeof(struct data), 1, myfile);     // WAV File Data Chunk

    //out.left=left;

    if (h2.dwBitsPerSample==8)
    {
        if(h2.wChannels==1)
        {
            left=malloc(h3.dwChunkSize*4);
            //right=malloc(h3.dwChunkSize*4);
            //out.length=h3.dwChunkSize;
        }
        if(h2.wChannels==2)
        {
            left=malloc(h3.dwChunkSize*2);
            right=malloc(h3.dwChunkSize*2);
            //out.length=h3.dwChunkSize/2;
        }

    }

    if (h2.dwBitsPerSample==16)
    {
        if(h2.wChannels==1)
        {
            left=malloc(h3.dwChunkSize*2);
            //right=malloc(h3.dwChunkSize*2);
            //out.length=h3.dwChunkSize/2;
        }
        if (h2.wChannels==2)
        {
            left=malloc(h3.dwChunkSize);
            right=malloc(h3.dwChunkSize);

            length=h3.dwChunkSize/4;
        }

    }

    if (h2.dwBitsPerSample==32)
    {
        if(h2.wChannels==1)
        {
            left=malloc(h3.dwChunkSize);
            //right=malloc(h3.dwChunkSize*2);
            //out.length=h3.dwChunkSize/4;
        }
        if (h2.wChannels==2)
        {
            left=malloc(h3.dwChunkSize/2);
            right=malloc(h3.dwChunkSize/2);

            //out.length=h3.dwChunkSize/8;
        }
    }


    wav_print(h1,h2,h3); //Print WAV File Header Info

    wav_process(h1,h2,h3,myfile,left,right);



    printf("\nMADE IT PAST WAV_PROCESS\n");

    end_test(h1,h2,h3,left,right);

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
/*


    fclose(myfile);

    printf("Length of Array(left) = %u\n", length);

    printf("\nMADE IT TO THE RETURN IN WAV_MAIN\n");

    return length;
// return (h2,h3,left); //"h2" is the format array of the WAV file, h"3" is the data chunk of the WAV file, "left" is the single array to use for processing
// length of the array of a 16bit WAV file = h3.dwChunkSize/4
}
*/
