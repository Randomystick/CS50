#include <cs50.h>
#include <stdio.h>


int main()
{
    // GET INPUT
    string input = get_string("Text: ");
    //DEBUG// printf("%s\n", input);
    
    
    
    // FIND W, TOTAL NO OF WORDS IN TEXT | sentence will not start or end with a space; a sentence will not have multiple spaces in a row.
    int words = 0;
    for (int i = 0; input[i] != '\0'; i++) // while haven't reach null terminator of string
    {
        if (input[i] == ' ') // when reach a space
        {
            words++;
        }
    }
    // Add one more for the last word in the whole text that doesn't have a space after it
    words++;
    //DEBUG// printf("words is %i\n", words);
    
    
    
    // FIND L, AVG NO OF LETTERS PER 100 WORDS IN TEXT | LETTERS = A-Za-z
    int letters = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if( (input[i]>='a' && input[i]<='z') || (input[i]>='A' && input[i]<='Z') )
        {
            letters++;
        }
    }
    // NOTE: integer division = get integer result no matter what, decimals will be discard.
    // SOLN: Cast to float to preserve decimals
    float L = (float)letters / (float)words * 100;
    //DEBUG// printf("letters is %i\n", letters); printf("L is %f\n", L);
    
    
    
    // FIND S, AVG NO OF SENTENCES PER 100 WORDS IN TEXT | SENTENCE END = . ! ?
    int sentences = 0;
    for (int i = 0; input[i] != '\0'; i++)
    {
        if( (input[i] == '.') || (input[i] == '!') || (input[i] == '?') )
        {
            sentences++;
        }
    }
    float S = (float)sentences / (float)words * 100;
    //DEBUG//printf("sentences is %i\n", sentences);printf("S is %f\n", S);



    // FIND INDEX
    int index = 0.0588 * L - 0.296 * S - 15.8;
    // NOTE: C rounds numbers down no matter what (Grade 4.9 -> Grade 4 -> wrong)
    // SOLN: Check if decimal is >=0.5 and round up if needed
    if ( ((float)(0.0588 * L - 0.296 * S - 15.8) - index) >= 0.5 )
    {
        index++;
    }
    
    //DEBUG//printf("index is %i\n", index);
    
    
    // PRINT GRADE LEVEL
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

    
    return 0;
}
