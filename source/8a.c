#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 256

struct command
{
    char operation[4];
    int value;
    int times_executed;
};

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/8.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        int rows = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            rows++;
        }

        printf("Number of rows in input file: %d\n", rows);

        struct command* commands = malloc(sizeof(struct command) * rows);

        rewind(fp);

        int command_count = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            struct command* temp = &commands[command_count++];

            sscanf(buf, "%s %d", temp->operation, &temp->value);

            temp->times_executed = 0;
        }

        int accumulator = 0;

        struct command* temp = &commands[0];

        while (!temp->times_executed)
        {
            temp->times_executed++;

            if (!strcmp("jmp", temp->operation))
            {
                temp += temp->value;    
            }
            else if (!strcmp("acc", temp->operation))
            {
                accumulator += temp->value;
                temp++;
            }
            else if (!strcmp("nop", temp->operation))
            {
                temp++;
            }
        }

        printf("Accumulator: %d\n", accumulator);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}