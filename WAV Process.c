//Tyler Kupczak
//WAV file processing using binary

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct header
{
    char sGroupID[4]; //RIFF indicates Resource Interchange File Format
    unsigned int dwFileLength; // Total file length (in bytes) minus 8 (8 bytes taken by RIFF)
    char sRiffType[4]; // WAVE, identifies file type
};

struct format
{
    char sGroupID[4]; // Four bytes: "fmt" indicates format chunk
    unsigned int dwChunkSize; //Length of header in bytes
    unsigned short wFormatTag; // 1 (MS PCM)
    unsigned short wChannels; // Number of channels
    unsigned int dwSamplesPerSec; // Audio Sample Rate
    unsigned int dwAvgBytesPerSec; // estimate RAM allocation
    unsigned short wBlockAlign; // sample frame size, in bytes
    unsigned short dwBitsPerSample; // bits per sample
};

struct data
{
    char sGroupID[4]; //Four bytes: "data" indicates data chunk
    unsigned int dwChunkSize;

};

void wav_print(struct header h1, struct format h2, struct data h3)
{
    printf("Header Group ID: %.4s\n", h1.sGroupID);
    printf("File Length: %u\n", h1.dwFileLength);
    printf("Riff Type: %.4s\n", h1.sRiffType);
    printf("\nFormat Group ID: %.4s\n", h2.sGroupID);
    printf("Chunk Size(Header length?): %u\n", h2.dwChunkSize);
    printf("Format Tag: %u\n", h2.wFormatTag);
    printf("Number of Channels: %u\n", h2.wChannels);
    printf("Sample Rate: %uHz\n", h2.dwSamplesPerSec);
    printf("Average Bps (Sample Rate*Frame Size): %u Bps\n", h2.dwAvgBytesPerSec);
    printf("Sample Frame Size: %u Bytes\n", h2.wBlockAlign);
    printf("Bit Rate: %u-bit\n", h2.dwBitsPerSample);
    printf("\nData Group ID: %.4s\n", h3.sGroupID);
    printf("Chunk Size (Bytes): %u\n", h3.dwChunkSize);
}


//NEED TO UPDATE 1CH FUNCTIONS TO FILL IN LEFT CHANNEL ARRAY

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
                printf("Sample: %u\t\tLeft(Mono): %f\n",j+1,mono[j]); //Visual representation of channels being filled out
            }
        }
}

void wav_1ch_16bit (struct header h1, struct format h2, struct data h3, FILE*myfile, int test, float *left, float *right)
{

    short *mono=malloc(h3.dwChunkSize); // create mono array

    printf("\nCREATED short mono array!\n");

    fread(mono, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in short mono array!!!!\n");

    for(int j=0;j<h3.dwChunkSize/2;j++)
        {
            left[j]=(float)mono[j];
            if(test==1)
            {
                //printf("Sample: %u\t\tLeft(Mono): %f\n",j+1,mono[j]); //Visual representation of channels being filled out
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[0]);
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
                printf("Sample: %u\t\tLeft: %hi\t\tRight: %hi\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
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

    printf("\nCREATED short wav_array, left, and right arrays!\n");
    fread(wav_array, h2.wBlockAlign/h2.wChannels, h3.dwChunkSize/(h2.wBlockAlign/h2.wChannels), myfile); //fill in wav_array, # of bytes per sample per channel, number of samples (chunksize (bytes)/ # of bytes per sample), location to read from

    printf("\nFilled in short wav_array!!!\n");
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

    printf("FILLED IN LEFT AND RIGHT CHANNEL ARRAYS!!!!");
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
                printf("Sample: %u\t\tLeft: %hi\t\tRight: %hi\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
            j++; //next sample in each channel
        }

    printf("FILLED IN LEFT AND RIGHT CHANNEL ARRAYS!!!!");
}


//pg.313 in textbook ENGINEERING PROBLEM SOLVING WITH C for dynamic memory allocation (malloc)

void end_test(struct header h1, struct format h2, struct data h3, float *left, float *right)
{
int test=0; //scanf input for printing data of channel arrays
int input=0; //scanf input for testing data from end of song in seconds
unsigned long test_end; //variable to print sample and value


printf("Would you like to print data of the channel arrays?(press 1 for yes or 0 for no)");
scanf("%i",&test);

if(h2.dwBitsPerSample==8)
{
   if(test==1)
       {
          for (int j=0;j<h3.dwChunkSize/2;j++)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
       }
}

if(h2.dwBitsPerSample==16)
{
   if(test==1)
       {
          for (int j=0;j<h3.dwChunkSize/4;j++)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
       }
}

if(h2.dwBitsPerSample==32)
{
   if(test==1)
       {
          for (int j=0;j<h3.dwChunkSize/8;j++)
            {
                printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",j+1,left[j],right[j]); //Visual representation of channels being filled out
            }
       }
}



printf("\n\nINPUT: Choose a time (seconds) from the end of the wav file to test:"); //Test array values at (input) seconds from end of song
scanf("%d", &input);
test_end=h3.dwChunkSize/h2.wBlockAlign-(input*h2.dwSamplesPerSec); //samples (chunk size (bytes) / 4 bytes per sample) - seconds (seconds * sample rate)

printf("Sample: %u\t\tLeft: %f\t\tRight: %f\n",test_end+1,left[test_end],right[test_end]);

}

//THIS FUNCTION IS TO DESIGNATE WHICH FUNCTION TO RUN IF MAKING SEPARATE FUNCTIONS PER TYPE OF WAV FILE (BIT, CHANNEL)

void wav_process(struct header h1, struct format h2, struct data h3, FILE*myfile, float *left, float *right)
{
    int test=0;
    printf("Would you like to print data while filling out channel arrays?(press 1 for yes or 0 for no)");
    scanf("%i",&test);

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


int main()
{

struct header h1;
struct format h2;
struct data h3;
float *left;
float *right;


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

    if (h2.dwBitsPerSample==8)
    {
        if(h2.wChannels==1)
        {
            left=malloc(h3.dwChunkSize*4);
            //right=malloc(h3.dwChunkSize*4);
        }
        if(h2.wChannels==2)
        {
            left=malloc(h3.dwChunkSize*2);
            right=malloc(h3.dwChunkSize*2);
        }

    }

    if (h2.dwBitsPerSample==16)
    {
        if(h2.wChannels==1)
        {
            left=malloc(h3.dwChunkSize*2);
        }
        if (h2.wChannels==2)
        {
            left=malloc(h3.dwChunkSize);
            right=malloc(h3.dwChunkSize);
        }

    }

    if (h2.dwBitsPerSample==32)
    {
        left=malloc(h3.dwChunkSize/2);
        right=malloc(h3.dwChunkSize/2);
    }


    wav_print(h1,h2,h3); //Print WAV File Header Info

    wav_process(h1,h2,h3,myfile,left,right);



    printf("\nMADE IT PAST WAV_PROCESS\n");

    end_test(h1,h2,h3,left,right);

    }

/* POSSIBLE WAY TO CREATE ERROR MESSAGE IF CODE FAILS TO CREATE ARRAY, LOOK UP IN TEXT BOOK
switch (x);
case (h2.)
default
{
    printf("\nERROR: Unable to create wav_array");
}
*/





    fclose(myfile);

    return 0;
// return (h2,h3,left); //"h2" is the format array of the WAV file, h"3" is the data chunk of the WAV file, "left" is the single array to use for processing
// length of the array of a 16bit WAV file = h3.dwChunkSize/4
}
