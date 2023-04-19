#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    // TODO

    string message = get_string("Message: ");

    // MAKE CONVERSATION AND PRINT ROW FOR EACH CHARACHTER

    for (int l = 0; l < strlen(message); l++)
    {
        // GIVEN DECIMAL
        int my_dec = (int) message[l];


        // DEFINE BIT ARRAY
        int my_bits[8];


        // CONVERT DECIMAL TO BITS
        int i = 0;
        while (my_dec > 1)
        {
            my_bits[i] = my_dec % 2;
            my_dec = (int)(my_dec / 2);

            i++;
        }
        my_bits[i] = 1;
        i++;


        // COMPLETE 8 BITS
        while (i < 8)
        {
            my_bits[i] = 0;
            i++;
        }


        // PRINT AS REVERSE
        for (int k = 7; -1 < k; k--)
        {
            //printf("%i", my_bits[k]);
            print_bulb(my_bits[k]);
        }
        printf("\n");
    }
}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}

