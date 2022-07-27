#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// declare functions
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

// Main function
int main(void)
{
    // Ask user for sentence input
    string text = get_string("Text:");

    // Find the metrics of the inputted text
    float c = count_letters(text);
    float wc = count_words(text);
    float sc = count_sentences(text);
    // Calculation of Coleman-Liau Index
    float L = c / wc * 100;
    float S = sc / wc * 100;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // rounding the index
    int grade = (int)round(index);

    // Printing out grade
    if (1 > grade)
    {
        printf("Before Grade 1\n");
    }
    else if (1 <= grade && 16 > grade)
    {
        printf("Grade %d\n", grade);
    }
    else if (16 <= grade)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Error\n");
    }
}

// function to count letters
int count_letters(string text)
{
    int i;
    int c = 0;
    // Check each char if it is an ASCII letter value
    for (i = 0; i < strlen(text); ++i)
    {
        if ((65 <= (int)text[i] && 90 >= (int)text[i]) || (97 <= (int)text[i] && 122 >= (int)text[i]))
        {
            c++;
        }
    }
    return c;
}

// function to count words
int count_words(string text)
{
    int i;
    // wc starts at 1 as the number of words is always number of sentences +1
    int wc = 1;
    // check each char in string if it is a space and also not just a double space
    for (i = 0; i < strlen(text); ++i)
    {
        if ((int)text[i] == 32 && (int)text[i + 1] != 32)
        {
            wc++;
        }
    }
    return wc;
}

// function to count sentences
int count_sentences(string text)
{
    int i;
    int sc = 0;
    // check each char for ! ? or . indicating the amount of sentences
    for (i = 0; i < strlen(text); ++i)
    {
        if ((int)text[i] == 63 || (int)text[i + 1] == 33 || (int)text[i + 1] == 46)
        {
            sc++;
        }
    }
    return sc;
}