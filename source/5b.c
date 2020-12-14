#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 256
#define SEATS_SIZE 1024 

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/5.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        char seats[SEATS_SIZE] = {0};
        int largest_uuid = 0;

        while (fgets(buf, BUFFER_MAX, fp) && !feof(fp))        
        {
            char* c = buf;
            int row = 0;
            int col = 0;
            int min = 0;
            int max = 127;

            while (*c != '\n')
            {
                if (*c == 'F' || *c == 'L')
                {
                    max = min + (max-min) / 2;
                }
                else if (*c == 'B' || *c == 'R')
                {
                    min = max - (max-min) / 2;
                }

                if (max == min)
                {
                    if (row)
                    {
                        col = max;
                    }
                    else
                    {
                        row = max;

                        min = 0;
                        max = 7;
                    }
                }
    
                c++;
            }

            int uuid = row*8+col;

            seats[uuid] = 1;

            if (uuid > largest_uuid)
            {
                largest_uuid = uuid;
            }
        }

        printf("Largest UUID: %d\n", largest_uuid);

        int first_seat_taken_found = 0;

        for (int i = 0; i < SEATS_SIZE; i++)
        {
            if (!seats[i])
            {
                if (first_seat_taken_found)
                {
                    printf("Seat found: %d\n", i);
                    break;
                }
            }
            else if (!first_seat_taken_found)
            {
                first_seat_taken_found = 1;
            }
        }
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}