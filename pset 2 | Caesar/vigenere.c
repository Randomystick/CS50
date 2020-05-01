// CIPHER.C -- ROTATE (ENCRYPT) TEXT USING USER-INPUTTED CIPHER

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int shift(char c);

int main(int argc, string argv[]) 
{
    
    // VALIDATING THE INPUT
    bool isValid = 1;
    if (argc != 2) 
    {
        printf("Usage: ./caesar keyword\n");
        return 1;
    }
    else 
    {
        for (int i = 0, n=strlen(argv[1]); i<n; i++) 
        {
            if ( !(isalpha(argv[1][i])) ) 
            {
                isValid = 0;
            }
        }
    }
    char KEYWORD[strlen(argv[1])];

    if (isValid)
    {
        strcpy(KEYWORD, argv[1]);
    }
    else
    {
        printf("Usage: ./caesar keyword\n");
        return 1;
    } 
    // VALIDATING INPUT END
    
    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    
    //PRINTING THE ENCRYPTED TEXT
    int k=0;
    for (int i = 0, j=strlen(text); i < j; i++) 
    {
        int KEYWORDshift = shift( KEYWORD[k % (strlen(argv[1])) ] );
        if (text[i] >= 65 && text[i] <= 90) //Capital A to Z
        {
            int textInt = (text[i] + (KEYWORDshift%26)); //Ensure text+KEY doesn't exceed 90 by more than 1 iteration of A-Z (ie 26)
            if (textInt > 90) { textInt = textInt % 91 + 65; } //Normalise textInt to be within A-Z
            printf("%c", textInt);
            k++;
        }
        else if (text[i] >= 97 && text[i] <= 122) //Same thing for small a-z
        {
            int textInt = (text[i] + (KEYWORDshift%26));
            if (textInt >= 123) { textInt = textInt % 123 + 97; }
            printf("%c", textInt);
            k++;
        }
        else { printf("%c", text[i]); } //punctuations
    }
    printf("\n"); //endline

    return 0;
}



int shift(char c)
{
    int KEYWORDshift;
    c = toupper(c);
    KEYWORDshift = c - 65;
    return KEYWORDshift;
}

