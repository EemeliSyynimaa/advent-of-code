#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSWERS_SIZE 26
#define BUFFER_MAX 256

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/6.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        char answers[ANSWERS_SIZE] = {0};
        unsigned int count_total = 0;
        unsigned int people_in_group = 0;

        while (1)
        {
            fgets(buf, BUFFER_MAX, fp);

            if (buf[0] == '\n' || feof(fp))
            {
                unsigned int count = 0;

                for (int i = 0; i < ANSWERS_SIZE; i++)
                {
                    if (answers[i] == people_in_group)
                    {
                        count++; 
                    }

                    answers[i] = 0;
                }

                count_total += count;
                people_in_group = 0;
            }
            else
            {
                people_in_group++;

                char* c = buf;

                while (*c != '\n')
                {
                    int i = *c - 'a';
                    answers[i]++;
                    c++;
                }
            }

            if (feof(fp))
            {
                break;
            }
        }

        printf("Answers total: %d\n", count_total);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}