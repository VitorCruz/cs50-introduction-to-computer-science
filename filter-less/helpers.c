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
            int sum = 0;
            int avg = 0;
            sum += image[i][j].rgbtBlue;
            sum += image[i][j].rgbtGreen;
            sum += image[i][j].rgbtRed;
            avg = (int) round(sum / 3.0);
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;

            int new_blue = (int) round(.272 * r + .534 * g + .131 * b);
            int new_green = (int) round(.349 * r + .686 * g + .168 * b);
            int new_red = (int) round(.393 * r + .769 * g + .189 * b);

            image[i][j].rgbtBlue = new_blue > 255 ? 255 : new_blue;
            image[i][j].rgbtGreen = new_green > 255 ? 255 : new_green;
            image[i][j].rgbtRed = new_red > 255 ? 255 : new_red;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2.0; j++)
        {
            int b = image[i][j].rgbtBlue;
            int g = image[i][j].rgbtGreen;
            int r = image[i][j].rgbtRed;

            image[i][j].rgbtBlue = image[i][width - j].rgbtBlue;
            image[i][width - j].rgbtBlue = b;

            image[i][j].rgbtGreen = image[i][width - j].rgbtGreen;
            image[i][width - j].rgbtGreen = g;

            image[i][j].rgbtRed = image[i][width - j].rgbtRed;
            image[i][width - j].rgbtRed = r;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img2[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            img2[i][j] = image[i][j];
        }
    }


    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int quantity = 0;
            int blue = 0;
            int green = 0;
            int red = 0;

            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    if (i + y >= 1 && i + y <= height && j + x >= 1 && j + x <= width)
                    {
                        blue += img2[i + y][j + x].rgbtBlue;
                        green += img2[i + y][j + x].rgbtGreen;
                        red += img2[i + y][j + x].rgbtRed;
                        quantity += 1;
                    }
                }
            }
            image[i][j].rgbtBlue = (int) round(blue / (float) quantity);
            image[i][j].rgbtGreen = (int) round(green / (float) quantity);
            image[i][j].rgbtRed = (int) round(red / (float) quantity);
            }
        }
    }
