//RECOVER.C

// ===========================================
// 0xff 0xd8 0xff      255 216 255
// from first byte to third byte, left to right.
// The fourth byte, meanwhile, is either 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef.  224 - 239
// Put another way, the fourth byte’s first four bits are 1110.

// digital cameras often initialize cards with a FAT file system whose "block size" is 512 bytes (B).
// The implication is that these cameras only write to those cards in units of 512 B.
// A photo that’s 1 MB (i.e., 1,048,576 B) thus takes up 1048576 ÷ 512 = 2048 "blocks" on a memory card.
// But so does a photo that’s, say, one byte smaller (i.e., 1,048,575 B)! The wasted space on disk is called "slack space."


// When executed, your program should recover every one of the JPEGs from card.raw, storing each as a separate file in your current working directory.
// Your program should number the files it outputs by naming each ###.jpg, where ### is three-digit decimal number from 000 on up. (Befriend sprintf.)

// ===========================================


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> // for uint8_t
#include <stdbool.h> // for bool
#include <string.h> // for strlen

typedef uint8_t BYTE;
FILE *fp;


void openNewJPG(int currentJPGnumber);


int main(int argc, char *argv[])
{
    //ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover image");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }


    //===============================================

    BYTE buffer[512]; // buffer = an array of 512 bytes
    bool currentlyInJPG = 0; // initially not writing in JPG file
    int currentJPGnumber = 0;

    while ((fread(buffer, 1, sizeof(buffer), file)) == 512) // while EOF is not reached yet
    {

        if ( (buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] >= 0xe0 && buffer[3] <= 0xef) ) // has JPG
        {
            if (currentlyInJPG) // found a new JPG
            {
                fclose(fp); // quit current JPG
                openNewJPG(currentJPGnumber); // create new file. &a indicates pointer to a (address of variable a)
                currentJPGnumber++;
                fwrite( buffer , 1 , sizeof(buffer) , fp );// write into this new JPG
            }
            else // found the first JPG
            {
                openNewJPG(currentJPGnumber); // create new file
                currentJPGnumber++;
                currentlyInJPG = 1;
                fwrite( buffer , 1 , sizeof(buffer) , fp ); // write into this new JPG
            }
        }
        else // no JPG
        {
            if (currentlyInJPG)
            {
                fwrite( buffer , 1 , sizeof(buffer) , fp ); // continue writing into current JPG
            }
            //else
            //{
                // do nothing; no JPG has been found so far
            //}
        }
    } // end of reading jpg

} //end of program


void openNewJPG(int currentJPGnumber)
{
    char fileNumber[3]; // 0 0 x
    sprintf(fileNumber, "%03d", currentJPGnumber); // %03d means "format the integer with 3 digits, left padding it with zeroes"
    char *dotJPG = ".jpg";
    //  strcat(fileNumber, dotJPG); // concatenate .JPG onto 00x
    char fileName[strlen(fileNumber)+strlen(dotJPG)+1];
    snprintf( fileName, sizeof( fileName ), "%s%s", fileNumber, dotJPG );
    fp = fopen( fileName, "w" );
}
