#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for the correct amount of arguments
    if (argc != 2)
    {
        printf("argument is not 1\n");
        return 1;
    }
    // open file
    FILE *input = fopen(argv[1], "r");

    // check if file opens
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // declare variables
    FILE *img = NULL;
    char filename[8];
    int BLOCK_SIZE = 512;
    unsigned char buffer[512];
    int imgnum = 0;

    // while reading blocks of size 512 continue
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // if first 4 bytes of block are defn of image then create new file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // but for the first image, close the current image
            if (!(imgnum == 0))
            {
                fclose(img);
            }
            // create new file
            sprintf(filename, "%03i.jpg", imgnum);
            img = fopen(filename, "w");
            imgnum++;
        }
        // if the first image has been activated then start writing
        if (!(imgnum == 0))
        {
            fwrite(&buffer, 1, BLOCK_SIZE, img);
        }
    }

    // Close file and last image
    fclose(input);
    fclose(img);
}