#include <stdio.h>
#include <stdlib.h>
int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/3.txt", "r");

    if (fp)
    {
        // Calculate width
        int width = 0;

        while (fgetc(fp) != '\n')
        {
            width++;
        }

        rewind(fp);

        // Calculate height
        char c;
        int height = 0;
        while ((c = fgetc(fp)) != EOF)
        {
            if (c == '\n')
            {
                height++;
            }
        }

        rewind(fp);

        printf("Map size: %d x %d\n", width, height);

        int map_size = width*height;
        int i = 0;
        char* map = malloc(map_size);

        while((c = fgetc(fp)) != EOF && i < map_size)
        {
            if (c != '\n')
            {
                map[i++] = c;
            }
        }

        fclose(fp);

        int x = 0;
        int y = 0;
        int trees = 0;

        while (y < height)
        {
            if (map[y * width + x] == '#')
            {
                trees++;
                map[y * width + x] = 'X';
            }
            else
            {
                map[y * width + x] = 'O';
            }

            if ((x += 3) >= width)
            {
                x -= width;
            }

            y++;

            printf("\n");
        }

        for (int y = 0; y < height; y++)
        {
            for (int x = 0; x < width; x++)
            {
                printf("%c", map[y * width + x]);
            }

            printf("\n");
        }

        printf("%d trees on slope\n", trees);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}