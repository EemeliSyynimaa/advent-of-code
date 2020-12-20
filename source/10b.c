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

void check_possibilities(int32_t* value, int32_t* end, uint64_t* possibilities)
{
    int32_t* next = value + 1;

    while ((*next - *value) <= 3)
    {
        if (*next == *end)
        {
            (*possibilities)++;
        }
        else
        {
            check_possibilities(next, end, possibilities);
        }

        next++;
    }
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

        int32_t* values = malloc(sizeof(int32_t) * rows + 1);

        rewind(fp);

        uint32_t value_count = 0;

        while(fgets(buf, BUFFER_MAX, fp))
        {
            sscanf(buf, "%d", &values[value_count++]);
        }

        values[value_count++] = 0;

        sort(values, value_count);

        for (uint32_t i = 0; i < value_count; i++)
        {
            printf("%d\n", values[i]);   
        }
 
        fflush(stdout);

        uint32_t* current = values;
        uint32_t* end = &values[value_count-1];
        uint64_t possibilities_total = 1;

        while (current != end)
        {
            uint32_t values_in_series = 0;
            uint32_t* next = current + 1;

            while (1)
            {
                values_in_series++;

                uint32_t possibilities = 0;

                for (uint32_t i = 0; i < 3; i++)
                {
                    if (*(next+i) - *next <= 2)
                    {
                        possibilities++;
                    }
                    else
                    {
                        break;
                    }
                }

                if (possibilities <= 1)
                {
                    break;
                }
                else
                {
                    next++;
                }
            }

            uint64_t possibilities = 0;

            check_possibilities(current, current + values_in_series,
                &possibilities);

            possibilities_total *= possibilities;

            current += values_in_series;
        }
        
        printf("Different ways: %llu\n", possibilities_total);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}