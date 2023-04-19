#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // TAKE FILENAME
    if (argc == 2)
    {
        char *input = argv[1];
        FILE *f = fopen(input, "r");

        // CHECK FILE EXIST
        if (f == NULL)
        {
            printf("Error! Wrong file");
            return 2;
        }

        // fread(buffer, 512, 1, f);

        FILE *img = NULL;
        BYTE buffer [512];
        int count = 0;
        char fileName[8];

        while (fread(&buffer, 512, 1, f) == 1)
        {
            // FIND CORRECT BUFFER
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                if (count > 0)
                {
                    fclose(img);
                }

                sprintf(fileName, "%03i.jpg", count);
                img = fopen(fileName, "w");

                count++;
            }
            // WRITE BUFFER TO FILE
            if (count > 0)
            {
                fwrite(&buffer, 512, 1, img);
            }
        }

        // MEMORY FREE
        fclose(f);
        fclose(img);

        return 0;
    }
    else
    {
        printf("Error! Right using is: > ./recover <file name>");
        return 1;
    }
}