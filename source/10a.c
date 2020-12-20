#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_MAX 256

void swap(int32_t* a, int32_t* b)
{
    int32_t temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int32_t* values, uint32_t count)
{
    uint32_t left = count - 1;

    while (left)
    {
        for (uint32_t i = 0; i < left; i++)
        {
            if (values[i] > values[i+1])
            {
                swap(&values[i], &values[i+1]);
            }
        }

        left--;
    }
}

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/10.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        uint32_t rows = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            rows++;
        }

        printf("Number of rows in input file: %d\n", rows);

        int32_t* values = malloc(sizeof(int32_t) * rows);

        rewind(fp);

        uint32_t value_count = 0;

        while(fgets(buf, BUFFER_MAX, fp))
        {
            sscanf(buf, "%d", &values[value_count++]);
        }

        sort(values, value_count);

        uint32_t ones = 0;
        uint32_t threes = 0;
        uint32_t previous = 0;

        for (uint32_t i = 0; i < value_count; i++)
        {
            uint32_t difference = values[i] - previous;

            ones += (difference == 1) ? 1 : 0;
            threes += (difference == 3) ? 1 : 0;
            

            previous = values[i];
        }

        threes++;

        printf("Ones: %d Threes: %d Multiplied: %d\n", ones, threes, 
            ones * threes);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}