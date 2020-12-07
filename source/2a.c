#include <stdio.h>

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/2.txt", "r");

    if (fp)
    {
        int validPasswordCount = 0;

        while (!feof(fp))
        {
            int min = 0;
            int max = 0;
            int letterCount = 0;
            char letter;
            char readLetter;

            if (fscanf(fp, "%d-%d %c:", &min, &max, &letter) == EOF)
            {
                continue;
            }

            printf("%d-%d %c:", min, max, letter);

            while ((readLetter = fgetc(fp)) != '\n')
            {
                printf("%c", readLetter);
                
                if (readLetter == letter)
                {
                    letterCount++;
                }
            }
                
            if (letterCount >= min && letterCount <= max)
            {

                validPasswordCount++;
                printf("  VALID");
            }

            printf("\n");
        }

        printf("Valid passwords: %d\n", validPasswordCount);

        fclose(fp);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}