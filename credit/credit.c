#include <cs50.h>
#include <stdio.h>
#include <math.h>

// main function
int main(void)
{
    // Ask user for credit card number input
    unsigned long long Number = get_long("Number:");
    unsigned long long nDigit = Number;
    int length = floor(log10(Number)) + 1;

    // check if the credit card number is within the correct range
    if ((12 < length && length < 14) || (14 < length && length < 17))
    {
        // inialise variables
        int i;
        int doubleDig = 0;
        int singleDig = 0;
        int lastDigSum = 0;
        int modulo;
        int doubleNum;
        int singleNum;
        // Luhn's products
        for (i = 1; i < length; i += 2)
        {
            unsigned long long power = pow(10, i);
            doubleDig = doubleDig + (nDigit / power % 10) * 2 % 10 + (nDigit / power % 10) * 2 / 10 % 10;
            doubleNum = nDigit / power % 10;
        }
        // Luhn's addition
        for (i = 0; i < length; i += 2)
        {
            unsigned long long power = pow(10, i);
            singleDig = singleDig + (nDigit / power % 10);
            singleNum = nDigit / power % 10;
        }
        modulo = (singleDig + doubleDig) % 10;
        // is Luhn's algorithm satisfied
        if (modulo == 0)
        {
            // American Express Requirements
            if (length == 15 && singleNum == 3 && (doubleNum == 4 || doubleNum == 7))
            {
                printf("AMEX\n");
            }
            // MasterCard Requirements
            else if (length == 16 && doubleNum == 5 && 0 < singleNum && singleNum < 6)
            {
                printf("MASTERCARD\n");
            }
            // Visa Requirements
            else if ((length == 13 && singleNum == 4) || (length == 16 && doubleNum == 4))
            {
                printf("VISA\n");
            }
            else
            {
                printf("INVALID\n");
            }
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}
