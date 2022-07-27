// including external modules
#include <cs50.h>
#include <stdio.h>
 
//main function
int main(void)
{
    //asking user for height input
    int height = get_int("Height:");
    //checking the input is betwen 0 and 8
    if ((0 < height) && (height < 9))
    {
        //declare for loop variables
        int i;
        int j;
        int count = height;
        int k;
        int count2 = 1;
        //main for loop which determines number of lines
        for (i = 0; i < height; ++i)
        {
            //first for loop setting whitespace
            for (j = count; j > 1; --j)
            {
                printf(" ");
            }
            //second for look setting first wall
            for (k = 0; k < count2; ++k)
            {
                printf("#");
            }
            //setting gap
            printf("  ");
            //third for loop setting the second wall
            for (k = 0; k < count2; ++k)
            {
                printf("#");
            }
            printf("\n");
            //incrementing the wall widths in next line of main for loop
            count -= 1;
            count2 += 1;
        }
    }
    else
    {
        //restarting the main function if the first entered amount is not between 0 and 8
        main();
    }
}