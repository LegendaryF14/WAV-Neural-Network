#include <stdio.h>
#include "WAV_Header.h"

void wav_process(struct header h1, struct format h2, struct data h3, FILE*myfile, float *left, float *right)
{
    int test=0;
/*
                                                    printf("Would you like to print data while filling out channel arrays?(press 1 for yes or 0 for no)");
                                                    scanf("%i",&test);
*/
    if (h2.wChannels==1||2)
    {

        if (h2.wChannels==1)
        {
            if (h2.dwBitsPerSample==8)
            {
                wav_1ch_8bit(h1,h2,h3,myfile,test, left, right);
            }

            if (h2.dwBitsPerSample==16)
            {
                wav_1ch_16bit(h1,h2,h3,myfile,test, left, right);
            }

            if (h2.dwBitsPerSample==32)
            {
                wav_1ch_32bit(h1,h2,h3,myfile,test, left, right);
            }
        }

        if (h2.wChannels==2)
        {
            if (h2.dwBitsPerSample==8)
            {
                wav_2ch_8bit(h1,h2,h3,myfile,test, left, right);
            }

            if (h2.dwBitsPerSample==16)
            {
                wav_2ch_16bit(h1,h2,h3,myfile,test, left, right);
            }

            if (h2.dwBitsPerSample==32)
            {
                wav_2ch_32bit(h1,h2,h3,myfile,test, left, right);
            }

        }
    }
    else
    {
        printf("ERROR! Unable to determine WAV_Format");
    }
}
