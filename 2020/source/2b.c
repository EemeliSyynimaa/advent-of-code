#include <stdio.h>

#define BUFFER_MAX 255

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/2.txt", "r");

    if (fp)
    {
        int validPasswordCount = 0;

        while (!feof(fp))
        {
            int indexA = 0;
            int indexB = 0;
            char buffer[BUFFER_MAX];
            char letter;

            if (fscanf(fp, "%d-%d %c:", &indexA, &indexB, &letter) == EOF)
            {
                continue;
            }

            printf("%d-%d %c: ", indexA, indexB, letter);

            fgets(buffer, BUFFER_MAX, fp);

            printf("%s", buffer);

            int correctA = buffer[indexA] == letter;
            int correctB = buffer[indexB] == letter;

            if (correctA != correctB)
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