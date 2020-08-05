#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");

    if (!file)
    {
        printf("Cannot open %s for reading\n", argv[1]);
        return 1;
    }

    BYTE bytes[512];
    int image_count = 0;

    char filename[8];
    FILE *outptr = NULL;

    while (true)
    {
        size_t check = fread(bytes, sizeof(BYTE), 512, file);

        if (check == 0 && feof(file))
        {
            break;
        }

        bool jpeg_check = ((bytes[0] == 0xff) && (bytes[1] == 0xd8) && (bytes[2] == 0xff) && ((bytes[3] & 0xf0) == 0xe0));

        if (jpeg_check && (outptr != NULL))
        {
            fclose(outptr);
            image_count++;
        }

        if (jpeg_check)
        {
            sprintf(filename, "%03i.jpg", image_count);
            outptr = fopen(filename, "w");
        }

        if (outptr != NULL)
        {
            fwrite(bytes, 1, 512, outptr);
        }
    }

    fclose(outptr);

    fclose(file);



}
