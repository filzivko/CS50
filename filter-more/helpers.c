#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0;
            image[i][j].rgbtRed = image[i][j].rgbtGreen = image[i][j].rgbtBlue = round(average);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int widthloop = (width / 2);
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < widthloop; j++)
        {
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;

            int reverseloc = width - 1 - j;
            image[i][j].rgbtRed = image[i][reverseloc].rgbtRed;
            image[i][j].rgbtGreen = image[i][reverseloc].rgbtGreen;
            image[i][j].rgbtBlue = image[i][reverseloc].rgbtBlue;

            image[i][reverseloc].rgbtRed = tempRed;
            image[i][reverseloc].rgbtGreen = tempGreen;
            image[i][reverseloc].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // declare new temp image
    RGBTRIPLE tempimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int kstart = -1;
            int lstart = -1;
            int kend = 2;
            int lend = 2;
            int averagecount = 0;
            double averagedenom = 9.0;
            // top edge
            if (i == height - 1)
            {
                kend = 1;
                averagecount++;
            }
            // left edge
            if (j == 0)
            {
                lstart = 0;
                averagecount++;
            }
            // bottom edge
            if (i == 0)
            {

                kstart = 0;
                averagecount++;
            }
            // right edge
            if (j == width - 1)
            {
                lend = 1;
                averagecount++;
            }
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            int averageRed = 0;
            int averageGreen = 0;
            int averageBlue = 0;
            for (int k = kstart; k < kend; k++)
            {
                for (int l = lstart; l < lend; l++)
                {
                    totalRed = totalRed + image[i + k][j + l].rgbtRed;
                    totalGreen = totalGreen + image[i + k][j + l].rgbtGreen;
                    totalBlue = totalBlue + image[i + k][j + l].rgbtBlue;
                    // printf("locaiton KL k:%d,l:%d correspoinging to i: j: is %d,%d,%d\n", i + k, j + l, image[i + k][j + l].rgbtRed, image[i + k][j + l].rgbtGreen, image[i + k][j + l].rgbtBlue);
                }
            }

            // printf("averagedenom: %f, averagecount: %d\n", averagedenom, averagecount);
            // printf("locaiton IJ %d,%d is %d,%d,%d\n", i, j, image[i][j].rgbtRed, image[i][j].rgbtGreen, image[i][j].rgbtBlue);
            if (averagecount == 2)
            {
                averagedenom = 4.0;
            }
            if (averagecount == 1)
            {
                averagedenom = 6.0;
            }

            averageRed = (int)round(totalRed / averagedenom);
            averageBlue = (int)round(totalBlue / averagedenom);
            averageGreen = (int)round(totalGreen / averagedenom);

            tempimage[i][j].rgbtRed = averageRed;
            tempimage[i][j].rgbtGreen = averageGreen;
            tempimage[i][j].rgbtBlue = averageBlue;
        }
    }
    // set image to temp image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = tempimage[m][n].rgbtRed;
            image[m][n].rgbtGreen = tempimage[m][n].rgbtGreen;
            image[m][n].rgbtBlue = tempimage[m][n].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Cx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Cy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    RGBTRIPLE tempimage[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int kstart = -1;
            int lstart = -1;
            int kend = 2;
            int lend = 2;
            // init colour X and Y variables
            int Rx = 0;
            int Gx = 0;
            int Bx = 0;
            int Ry = 0;
            int Gy = 0;
            int By = 0;
            // inner loop vert
            for (int k = kstart; k < kend; k++)
            {
                // inner loop horizontal
                for (int l = lstart; l < lend; l++)
                {
                    // checking if edge or corner to not include value
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }

                    if (j + l < 0 || j + l > width - 1)
                    {
                        continue;
                    }
                    // adding respective X and Y values
                    Rx = Rx + image[i + k][j + l].rgbtRed * Cx[1 + k][1 + l];
                    Gx = Gx + image[i + k][j + l].rgbtGreen * Cx[1 + k][1 + l];
                    Bx = Bx + image[i + k][j + l].rgbtBlue * Cx[1 + k][1 + l];
                    Ry = Ry + image[i + k][j + l].rgbtRed * Cy[1 + k][1 + l];
                    Gy = Gy + image[i + k][j + l].rgbtGreen * Cy[1 + k][1 + l];
                    By = By + image[i + k][j + l].rgbtBlue * Cy[1 + k][1 + l];
                }
            }

            int resR = round(sqrt(Rx * Rx + Ry * Ry));
            int resG = round(sqrt(Gx * Gx + Gy * Gy));
            int resB = round(sqrt(Bx * Bx + By * By));

            tempimage[i][j].rgbtRed = (resR > 255) ? 255 : resR;
            tempimage[i][j].rgbtGreen = (resG > 255) ? 255 : resG;
            tempimage[i][j].rgbtBlue = (resB > 255) ? 255 : resB;
        }
    }
    // set image to temp image
    for (int m = 0; m < height; m++)
    {
        for (int n = 0; n < width; n++)
        {
            image[m][n].rgbtRed = tempimage[m][n].rgbtRed;
            image[m][n].rgbtGreen = tempimage[m][n].rgbtGreen;
            image[m][n].rgbtBlue = tempimage[m][n].rgbtBlue;
        }
    }
    return;
}
