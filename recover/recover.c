#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdint.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <math.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;


int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE_NAME\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    BYTE block[512];
    FILE *img = NULL;
    int file_count = 0;
    char filename[8];

    while (fread(block, sizeof(uint8_t), 512, file) == 512)
    {
        if (block[0] == 255 && block[1] == 216 && block[2] == 255 && block[3] >= 224 && block[3] <= 239)
        {
            file_count +=1;
            if (img == NULL)
            {
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", file_count);
                img = fopen(filename, "w");
            }
        }
        if (img != NULL)
        {
            fwrite(block, sizeof(uint8_t), 512, img);
        }
    }
    fclose(file);
    fclose(img);
}

