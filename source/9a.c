#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_MAX 256

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/9.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        uint32_t rows = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            rows++;
        }

        printf("Number of rows in input file: %d\n", rows);

        uint64_t* values = malloc(sizeof(uint64_t) * rows);

        rewind(fp);

        uint32_t value_count = 0;

        while(fgets(buf, BUFFER_MAX, fp))
        {
            sscanf(buf, "%lu", &values[value_count++]);
        }

        for (uint32_t i = 25; i < value_count; i++)
        {
            uint32_t found = 0;

            for (int j = i - 25; j < i - 1 && !found; j++)
            {
                for (int k = i - 24; k < i && !found; k++)
                {
                    if (values[j] + values[k] == values[i])
                    {
                        found = 1;
                    }
                }
            }

            if (!found)
            {
                printf("%lu\n", values[i]);
                break;
            }
        }
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}