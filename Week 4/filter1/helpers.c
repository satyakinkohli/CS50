#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float c = ((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3;

            image[i][j].rgbtRed = round(c);
            image[i][j].rgbtGreen = round(c);
            image[i][j].rgbtBlue = round(c);
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sepiaRed = .393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue;
            float sepiaGreen = .349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue;
            float sepiaBlue = .272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int r = image[i][j].rgbtRed;
            int g = image[i][j].rgbtGreen;
            int b = image[i][j].rgbtBlue;

            int r1 = image[i][width - 1 - j].rgbtRed;
            int g1 = image[i][width - 1 - j].rgbtGreen;
            int b1 = image[i][width - 1 - j].rgbtBlue;

            image[i][j].rgbtRed = r1;
            image[i][j].rgbtGreen = g1;
            image[i][j].rgbtBlue = b1;

            image[i][width - 1 - j].rgbtRed = r;
            image[i][width - 1 - j].rgbtGreen = g;
            image[i][width - 1 - j].rgbtBlue = b;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    float blurRed = 0, blurGreen = 0, blurBlue = 0, k = 0;

    int final_average[height][width][3];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            for (int s = -1; s < 2; s++)
            {
                for (int g = -1; g < 2; g++)
                {
                    if (((i + s > -1) && (i + s < height)) && ((j + g > -1) && (j + g < width)))
                    {
                        blurRed += (float)image[i + s][j + g].rgbtRed;
                        blurGreen += (float)image[i + s][j + g].rgbtGreen;
                        blurBlue += (float)image[i + s][j + g].rgbtBlue;

                        k += 1;
                    }
                }
            }

            final_average[i][j][0] = round(blurRed / k);
            final_average[i][j][1] = round(blurGreen / k);
            final_average[i][j][2] = round(blurBlue / k);

            blurRed = 0, blurGreen = 0, blurBlue = 0, k = 0;
        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = final_average[a][b][0];
            image[a][b].rgbtGreen = final_average[a][b][1];
            image[a][b].rgbtBlue = final_average[a][b][2];
        }
    }

    return;
}
