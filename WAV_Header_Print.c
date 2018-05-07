#include "WAV_Header.h"

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

