// CREDIT.C -- VERIFY A CREDIT CARD NUMBER FOR LEGITIMACY
// USING RECOMMENDED ARITHMETIC METHOD

#include <stdio.h>
#include <math.h>
#include <cs50.h>

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
                                                // printf("%f \n", creditLength);
    // Determine number of numbers to multiply
    int VALUE = creditLength - 1;
    
    // Obtain every other digit
    // Multiply them by 2
    // Add those products' digits
    int sum = 0;
    long otherDigi; 
    int otherDigit;
    for (double i = 1; i <= VALUE; i = i+2) {
        otherDigi = creditNo / (pow(10.0,i));
        otherDigit = otherDigi % 10;
                                             // printf("%d \n", otherDigit);
        otherDigit = otherDigit * 2;
        if (otherDigit >= 10) {
            otherDigit = otherDigit - 9;
        }
        sum += otherDigit;
    }
    
    // Sum of digits that weren't multiplied by 2
    int sumTwo = 0;
    long remainingDigi;
    int remainingDigit;
    for (double i = 0; i <= VALUE; i = i+2) {
    remainingDigi = creditNo / (pow(10.0,i));
    remainingDigit = remainingDigi % 10;
                                            // printf("%d \n", remainingDigit);
    sumTwo += remainingDigit;
    }
    
    int firstNo = creditNo / (pow(10.0, creditLength-1));
    int firstTwoNo = creditNo / (pow(10.0, creditLength-2));
                                            // printf("%d \n", firstTwoNo);
    
    // Final check
    int totalSum = sum + sumTwo;
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
