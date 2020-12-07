#include <stdio.h>

#define BUFFER_MAX 1024

int main(int argc, char** argv)
{
    int index = 0;
    int buffer[BUFFER_MAX];

    FILE* fp = fopen("../data/1.txt", "r");

    if (fp)
    {
        while (1)
        {
            if (EOF == fscanf(fp, "%d", &buffer[index]))
            {
                break;
            }

            index++;
        }

        fclose(fp);
    }

    for (int i = 0; i < index; i++)
    {
        for (int j = 1; j < index; j++)
        {
            for (int k = 2; k < index; k++)
            {
                if (buffer[i] + buffer[j] + buffer[k] == 2020)
                {
                    printf("Found it: %d * %d * %d = %d\n",
                        buffer[i], buffer[j], buffer[k], 
                        buffer[i] * buffer[j] * buffer[k]);
                    return 0;
                }
            }
        }
    }

    return 0;
}