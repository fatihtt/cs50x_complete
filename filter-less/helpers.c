#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // FIND AVERAGE VALUES
            int ort = round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            // SET VALUES
            image[i][j].rgbtRed = ort;
            image[i][j].rgbtGreen = ort;
            image[i][j].rgbtBlue = ort;
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
            // FIND AVERAGE VALUES
            int sepiaRed = round(0.393 * (float) image[i][j].rgbtRed + 0.769 * (float) image[i][j].rgbtGreen + 0.189 * (float) image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * (float) image[i][j].rgbtRed + 0.686 * (float) image[i][j].rgbtGreen + 0.168 * (float) image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * (float) image[i][j].rgbtRed + 0.534 * (float) image[i][j].rgbtGreen + 0.131 * (float) image[i][j].rgbtBlue);

            // CORRECT EXCESSIVE VALUES
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


            // SET VALUES
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
    RGBTRIPLE my_pixel[width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j <  round((float) width / 2); j++)
        {
            // ADD HORIZANTAL PIXELS AS REFLECTION
            //image[i][width + j] = image[i][width - 1 - j];
            my_pixel[j] = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = my_pixel[j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int ort_red = 0;
            int ort_green = 0;
            int ort_blue = 0;
            int ort_count = 0;

            RGBTRIPLE my_pixel = temp[height][width];
            if (i > 0)
            {
                if (j > 0)
                {
                    my_pixel = temp[i - 1][j - 1];
                    ort_red += my_pixel.rgbtRed;
                    ort_green += my_pixel.rgbtGreen;
                    ort_blue += my_pixel.rgbtBlue;
                    ort_count++;
                }

                my_pixel = temp[i - 1][j];
                ort_red += my_pixel.rgbtRed;
                ort_green += my_pixel.rgbtGreen;
                ort_blue += my_pixel.rgbtBlue;
                ort_count++;

                if (j < width - 1)
                {
                    my_pixel = temp[i - 1][j + 1];
                    ort_red += my_pixel.rgbtRed;
                    ort_green += my_pixel.rgbtGreen;
                    ort_blue += my_pixel.rgbtBlue;
                    ort_count++;
                }

            }

            if (j > 0)
            {
                my_pixel = temp[i][j - 1];
                ort_red += my_pixel.rgbtRed;
                ort_green += my_pixel.rgbtGreen;
                ort_blue += my_pixel.rgbtBlue;
                ort_count++;
            }

            my_pixel = temp[i][j];
            ort_red += my_pixel.rgbtRed;
            ort_green += my_pixel.rgbtGreen;
            ort_blue += my_pixel.rgbtBlue;
            ort_count++;

            if (j < width - 1)
            {
                my_pixel = temp[i][j + 1];
                ort_red += my_pixel.rgbtRed;
                ort_green += my_pixel.rgbtGreen;
                ort_blue += my_pixel.rgbtBlue;
                ort_count++;
            }

            if (i < height - 1)
            {
                if (j > 0)
                {
                    my_pixel = temp[i + 1][j - 1];
                    ort_red += my_pixel.rgbtRed;
                    ort_green += my_pixel.rgbtGreen;
                    ort_blue += my_pixel.rgbtBlue;
                    ort_count++;
                }

                my_pixel = temp[i + 1][j];
                ort_red += my_pixel.rgbtRed;
                ort_green += my_pixel.rgbtGreen;
                ort_blue += my_pixel.rgbtBlue;
                ort_count++;

                if (j < width - 1)
                {
                    my_pixel = temp[i + 1][j + 1];
                    ort_red += my_pixel.rgbtRed;
                    ort_green += my_pixel.rgbtGreen;
                    ort_blue += my_pixel.rgbtBlue;
                    ort_count++;
                }

            }

            int oort_red = round((float)ort_red / ort_count);
            int oort_green = round((float)ort_green / ort_count);
            int oort_blue = round((float)ort_blue / ort_count);

            image[i][j].rgbtRed = oort_red;
            image[i][j].rgbtGreen = oort_green;
            image[i][j].rgbtBlue = oort_blue;
        }
    }
    return;
}
