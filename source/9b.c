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

        uint64_t total = 0;
        uint64_t target = 393911906;
        uint64_t first = 0;

        for (uint32_t i = 0; i < value_count; i++)
        {
            total += values[i];

            while (total > target)
            {
                total -= values[first++];
            }

            if (total == target && first != i)
            {
                uint64_t largest = values[i];
                uint64_t smallest = values[i];

                for (int j = first; j < i; j++)
                {
                    if (values[j] > largest)
                    {
                        largest = values[j];
                    }
                    else if (values[j] < smallest)
                    {
                        smallest = values[j];
                    }
                }

                printf("Smallest: %lu, largest: %lu, weakness: %lu\n",
                    smallest, largest, smallest + largest);

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