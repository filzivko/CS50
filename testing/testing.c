#include <stdio.h>
#include <cs50.h>

#include <stdint.h>

int size = 1;
int array[1];

int height = 3;
int width = 3;


// Blur image
int main(void)
{
    // declare new temp image

    // // vertically loop to get the pixel of interest
    // for (int i = 0; i < height; i++)
    // {
    //     // horizontally loop to get the pixel of interest
    //     for (int j = 0; j < width; j++)
    //     {
    //         int kstart = -1;
    //         int lstart = -1;
    //         int kend = 2;
    //         int lend = 2;
    //         int averagecount = 0;
    //         double averagedenom = 9.0;

    //         if (i == 0)
    //         {
    //             kstart = 0;
    //             averagecount++;
    //         }
    //         if (j == 0)
    //         {
    //             lstart = 0;
    //             averagecount++;
    //         }
    //         if (i == height)
    //         {
    //             kend = 1;
    //             averagecount++;
    //         }
    //         if (j == width)
    //         {
    //             lend = 1;
    //             averagecount++;
    //         }

    //         int totalRed = 0;
    //         int totalGreen = 0;
    //         int totalBlue = 0;
    //         int averageRed = 0;
    //         int averageGreen = 0;
    //         int averageBlue = 0;
    //         // finding average around the pixel vertically looped
    //         for (int k = kstart; k < kend; k++)
    //         {
    //             // finding average around the pixel horizontally looped
    //             for (int l = lstart; l < lend; l++)
    //             {
    //                 totalRed = totalRed + image[i + k][j + l].rgbtRed;
    //                 totalGreen = totalGreen + image[i + k][j + l].rgbtGreen;
    //                 totalBlue = totalBlue + image[i + k][j + l].rgbtBlue;
    //             }
    //         }
    //         // printf("i:%d\n", i);
    //         // printf("j:%d\n", j);
    //         // printf("total red:%d\n", totalRed);
    //         // printf("total green:%d\n", totalGreen);
    //         // printf("total blue:%d\n", totalBlue);
    //         if (averagecount == 2)
    //         {
    //             averagedenom = 4.0;
    //         }
    //         if (averagecount == 1)
    //         {
    //             averagedenom = 6.0;
    //         }

    //         averageRed = (int)round(totalRed / averagedenom);
    //         averageBlue = (int)round(totalBlue / averagedenom);
    //         averageGreen = (int)round(totalGreen / averagedenom);

    //         tempimage[i][j].rgbtRed = averageRed;
    //         tempimage[i][j].rgbtGreen = averageGreen;
    //         tempimage[i][j].rgbtBlue = averageBlue;

    //         // printf("final average red:%d\n", averageRed);
    //         // printf("final average green:%d\n", averageGreen);
    //         // printf("final average blue:%d\n", averageBlue);
    //     }
    // }
    // // set image to temp image
    // for (int m = 0; m < height; m++)
    // {
    //     for (int n = 0; n < width; n++)
    //     {
    //         image[m][n].rgbtRed = tempimage[m][n].rgbtRed;
    //         image[m][n].rgbtGreen = tempimage[m][n].rgbtGreen;
    //         image[m][n].rgbtBlue = tempimage[m][n].rgbtBlue;
    //     }
    // }

    return;
}