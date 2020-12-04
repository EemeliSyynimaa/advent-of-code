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

        int steps_x[] = { 1, 3, 5, 7, 1 };
        int steps_y[] = { 1, 1, 1, 1, 2 };
        unsigned trees[5] = { 0 };

        int step_count = sizeof(steps_x) / sizeof(int); 
        int step_i = 0;

        printf("Steps: %d\n", step_count);

        while (step_i < step_count)
        {
            int x = 0;
            int y = 0;

            while (y < height)
            {
                if (map[y * width + x] == '#')
                {
                    trees[step_i]++;
                }

                if ((x += steps_x[step_i]) >= width)
                {
                    x -= width;
                }

                y += steps_y[step_i];
            }

            step_i++;
        }

        unsigned long trees_total = 1;

        for (int i = 0; i < step_count; i++)
        {
            printf("Trees %d: %d\n", i, trees[i]);
            trees_total = trees_total* trees[i];
        }

        printf("Trees total: %lu\n", trees_total);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}