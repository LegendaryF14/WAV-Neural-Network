#include <stdio.h>
#include "WAV_Header.h"

void end_test(struct header h1, struct format h2, struct data h3, float *left, float *right)
{
int test=0; //scanf input for printing data of channel arrays
int input=0; //scanf input for testing data from end of song in seconds
unsigned long test_end; //variable to print sample and value


printf("Would you like to print data of the channel arrays?(press 1 for yes or 0 for no)");
scanf("%i",&test);

if(test==1)
{

if(h2.dwBitsPerSample==8)
{
    if(h2.wChannels==1)
    {
        for (int j=0;j<h3.dwChunkSize;j++)
        {
            printf("Sample: %u\t\tLeft(mono): %f\n",j+1,left[j]); //Visual representation of channels being filled out
        }
    }

    if(h2.wChannels==2)
    {
        for (int j=0;j<h3.dwChunkSize/2;j++)
        {
            printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
        }
    }
}

if(h2.dwBitsPerSample==16)
{
    if(h2.wChannels==1)
    {
        for (int j=0;j<h3.dwChunkSize/2;j++)
        {
            printf("Sample: %u\t\tLeft(mono): %f\n",j+1,left[j]); //Visual representation of channels being filled out
        }
    }

    if(h2.wChannels==2)
    {
        for (int j=0;j<h3.dwChunkSize/4;j++)
        {
            printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
        }
    }
}


if(h2.dwBitsPerSample==32)
{
    if(h2.wChannels==1)
    {
        for (int j=0;j<h3.dwChunkSize/4;j++)
        {
            printf("Sample: %u\t\tLeft(mono): %f\n",j+1,left[j]); //Visual representation of channels being filled out
        }
    }

    if(h2.wChannels==2)
    {
        for (int j=0;j<h3.dwChunkSize/8;j++)
        {
            printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
        }
    }
}
}



printf("\n\nINPUT: Choose a time (seconds) from the end of the wav file to test:"); //Test array values at (input) seconds from end of song
scanf("%d", &input);
test_end=h3.dwChunkSize/h2.wBlockAlign-(input*h2.dwSamplesPerSec); //samples (chunk size (bytes) / 4 bytes per sample) - seconds (seconds * sample rate)

if(h2.wChannels==1)
{
   printf("Sample: %lu\t\tLeft(mono): %f\n",test_end+1,left[test_end]);
}
if(h2.wChannels==2)
{
   printf("Sample: %lu\t\tLeft: %f\t\tRight: %f\n",test_end+1,left[test_end],right[test_end]);
}

}
