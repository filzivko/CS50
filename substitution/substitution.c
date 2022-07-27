#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    // check if cipher was entered
    if (argc <= 1)
    {
        printf("Please enter a cipher code into the command line immediately after ./substituion.\n");
        return 1;
    }
    // run if cipher entered
    else if (argc == 2)
    {
        // check if 26 char
        if (strlen(argv[1]) == 26)
        {
            int i;
            for (i = 0; i < strlen(argv[1]); ++i)
            {
                // ASCII value
                int ASCII_val = tolower(argv[1][i]);

                // check if char is repeted
                int firstoccourance = strlen(index(argv[1], argv[1][i]));
                int lastoccourance = strlen(rindex(argv[1], argv[1][i]));

                if (firstoccourance != lastoccourance)
                {
                    printf("Please ensure that no character is repeated twice in the cipher.\n");
                    return 1;
                }
                // check if char is alphabetical
                if (97 > ASCII_val || ASCII_val > 122)
                {
                    printf("Please ensure that there are only alphabetical characters in the cipher.\n");
                    return 1;
                }
            }

            // print back ciphered code
            string plaintext = get_string("plaintext: ");
            printf("ciphertext: ");
            int j;
            for (j = 0; j < strlen(plaintext); ++j)
            {
                int ASCII_val_input = (int)plaintext[j];
                // apply lower case ciphers
                if (96 < ASCII_val_input && ASCII_val_input < 123)
                {
                    printf("%c", tolower(argv[1][ASCII_val_input - 97]));
                }
                // apply upper case ciphers
                else if (64 < ASCII_val_input && ASCII_val_input < 91)
                {
                    printf("%c", toupper(argv[1][ASCII_val_input - 65]));
                }
                else
                {
                    printf("%c", plaintext[j]);
                }
            }
            printf("\n");
            return 0;
        }
        else
        {
            printf("Please enter a cipher with 26 characters\n");
            return 1;
        }
    }
    // check if more than one type of argument was enterd
    else if (argc > 2)
    {
        printf("Please enter only ONE (1) cipher argument after ./subsitution\n");
        return 1;
    }
}