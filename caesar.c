// CIPHER.C -- ROTATE (ENCRYPT) TEXT USING USER-INPUTTED CIPHER

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[]) 
{
    // VALIDATING THE INPUT
    int KEY = 0;
    int isValid = 1;
    if (argc != 2) 
    {
        isValid = 0;
        return 1;
    }
    else 
    {
        for (int i = 0, n=strlen(argv[1]); i<n; i++) 
        {
            if ( !(isdigit(argv[1][i])) ) 
            {
                isValid--;
            }
        }
    }

    switch(isValid) {
        case 1:
            KEY = atoi(argv[1]);
            break;
        default:
            printf("Usage: ./caesar key\n");
            break;
    } 
    // VALIDATING INPUT END
    
    //PRINTING THE ENCRYPTED TEXT
    if (isValid == 1) {
        string text = get_string("plaintext: ");
        printf("ciphertext: ");
        for (int i = 0, n=strlen(text); i < n; i++) 
        {
            if (text[i] >= 65 && text[i] <= 90) //Capital A to Z
            {
                int textInt = (text[i] + (KEY%26));
                if (textInt > 90) { textInt = textInt % 91 + 65; }
                printf("%c", textInt);
            }
            else if (text[i] >= 97 && text[i] <= 122) 
            {
                int textInt = (text[i] + (KEY%26));
                if (textInt >= 123) { textInt = textInt % 123 + 97; }
                printf("%c", textInt);
            }
            else { printf("%c", text[i]); }
        }
        printf("\n");
    }
    
    return 0;
}
