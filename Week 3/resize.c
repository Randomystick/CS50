// RESIZE.C
// 24 bit = 3 bytes = 1 pixel
// fseek = adjust position of inptr and outptr
// fwrite and fread = write/read x amount of data from where inptr/outptr currently is - which is in turn set by fseek

// ERROR LOG:
// Problem: Trying to use biWidth and lineLength together, even though biWidth is in pixels, lineLength is in bytes.
// Solution: Add *3 to line 126 (int lineLengthInBytes = (biTwo.biWidth*3) + paddingTwo;)
// Problem: Defining lineStorage as a string, then not adding the null terminating character for it to be considered a string.
// Solution: Add and remove the null terminating character on lineStorage during the transfer.
// Problem: As it turns out you cannot insert data into a stream, only overwrite it. This makes doing vertical scaling 
// - and by extension doing horizontal scaling then vertical scaling sequentially - prohibitively complicated to do, 
// so a major rewrite is in order. Big oof
// Problem: outfile was opened as write only.
// Solution: open as write+read

// 16-Dec-19: Used different methodology - instead of copy pasting within outfile, 
// manipulate loops to do vertical scaling via horizontal scaling
// since vertical scaling is essentially doing horizontal scaling on a different row.
// USE PSEUDOCODE PLEASE IT MAKES EVERYTHING SO MUCH EASIER TO VISUALISE and abstract all the implementation details away


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // for uint8_t
#include "bmp.h"

void inToOut();

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]); //argv[1] is a string, cannot use casting
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w+");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }


    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    //CS50: MODIFYING bi AND bf VALUES BEFORE WRITING TO OUTFILE
    BITMAPINFOHEADER biTwo = bi;
    biTwo.biWidth = bi.biWidth * n;
    biTwo.biHeight = bi.biHeight * n;
    int paddingTwo = (4 - (biTwo.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    biTwo.biSizeImage = ( (sizeof(RGBTRIPLE)*biTwo.biWidth + paddingTwo) * abs(biTwo.biHeight) );
    BITMAPFILEHEADER bfTwo = bf;
    bfTwo.bfSize = biTwo.biSizeImage + sizeof(biTwo) + sizeof(bfTwo);

    // BITMAPFILEHEADER, is 14 bytes long
    // BITMAPINFOHEADER, is 40 bytes long

    // write outfile's BITMAPFILEHEADER
    fseek(outptr, 0, SEEK_SET);  //set current position of stream pointer (outptr) to the start
    fwrite(&bfTwo, sizeof(BITMAPFILEHEADER), 1, outptr);
    fwrite(&biTwo, sizeof(BITMAPINFOHEADER), 1, outptr);

    // HEADERS SETTLED

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4; // determine padding for infile
    int lineLengthOLD = bi.biWidth * sizeof(RGBTRIPLE) + padding; // biWidth is in pixels == RGBTRIPLE == 3 bytes. padding == bytes
    fseek(outptr, 54, SEEK_SET); //set outptr at start of first line

    int biHeight = abs(bi.biHeight);
    int biWidth = abs(bi.biWidth);
    for (int i = 0; i < biHeight; i++) // LOOP START // LOOP START // LOOP START
    {

        fseek(inptr, (54+(lineLengthOLD*i)), SEEK_SET); //set inptr at start of %iteration% line
        for (int j = 0; j < n; j++)
        {
            for (int iTO = 0; iTO < biWidth; iTO++) //inptr -> outptr horizontal scaling
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int iTOTwo = 0; iTOTwo < n; iTOTwo++)
                {
                    // write RGB triple to outfile, scaled horizontally
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            } //end of inptr -> outptr
            fseek(inptr, -(biWidth*3), SEEK_CUR); //inptr go back to start of first line
            for (int L = 0; L < paddingTwo; L++)
            {
                fputc(0x00, outptr);
            } //outptr add padding and remain
        }
    } // LOOP END // LOOP END // LOOP END

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
