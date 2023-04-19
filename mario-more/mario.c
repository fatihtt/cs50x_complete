#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // take the number and check if its 1-8

    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || 8 < height);


    // make the pyramid according to given height

    string row = "";
    for (int i = 0; i < height; i++)
    {
        int row_space_count = height - i - 1;
        int row_space_count2 = row_space_count;

        // first half

        while (row_space_count > 0)
        {
            printf(" ");
            row_space_count--;
        }

        int count_dash = i + 1;
        int count_dash2 = count_dash;
        while (count_dash > 0)
        {
            printf("#");
            count_dash--;
        }

        // half space

        printf("  ");

        // second half

        while (count_dash2 > 0)
        {
            printf("#");
            count_dash2--;
        }

        printf("\n");
    }
}