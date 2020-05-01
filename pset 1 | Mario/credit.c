// CREDIT.C -- VERIFY A CREDIT CARD NUMBER FOR LEGITIMACY
// USING RECOMMENDED ARITHMETIC METHOD
// UPDATED WITH FUNCTION (RULE D.R.Y)


#include <stdio.h>
#include <math.h>
#include <cs50.h>

int digitExtractor (double i, long creditNo, double VALUE) {
    int sum = 0;
    long digi; 
    int digit;
    for (double j = i; j <= VALUE; j = j+2) {
        digi = creditNo / (pow(10.0,j));
        digit = digi % 10;
        if (i == 1) {
            digit = digit * 2;
                if (digit >= 10) {
                        digit = digit - 9;
                }
        }
        sum += digit;
    }
    return sum;
}

int main(void) {
    long creditNo = get_long("Number: ");
    
    // Obtain length of credit card number
    long creditNoSave = creditNo;
    double creditLength = 0;
    while (creditNo > 0) {
	creditNo = creditNo / 10;
	creditLength+=1;
    }
    creditNo = creditNoSave;

    // Determine number of numbers to multiply
    int VALUE = creditLength - 1;
    
    // Obtain every other digit
    // Multiply them by 2
    // Add those products' digits
    int sumEveryOther = digitExtractor(1, creditNo, VALUE);
                                                // printf("%d \n", sumEveryOther);

    // Sum of digits that weren't multiplied by 2
    int sumRemaining = digitExtractor(0, creditNo, VALUE);
                                                // printf("%d \n", sumRemaining);

    int firstNo = creditNo / (pow(10.0, creditLength-1));
    int firstTwoNo = creditNo / (pow(10.0, creditLength-2));
    
    // Final check
    int totalSum = sumEveryOther + sumRemaining;
                                                // printf("%d \n", totalSum);

    if (creditLength < 13 || creditLength > 16 || (totalSum % 10 != 0)) {
        printf("INVALID\n");
    }
    else if (firstTwoNo == 34 || firstTwoNo == 37) {
            printf("AMEX\n");
        }
    else if (firstNo == 4){
            printf("VISA\n");
        }
    else if (firstTwoNo >= 51 && firstTwoNo <= 55){
            printf("MASTERCARD\n");
        }
    else {
            printf("INVALID\n");
        }

    return 0;
}
