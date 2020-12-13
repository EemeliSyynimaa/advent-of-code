#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 256

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/4.txt", "r");

    if (fp)
    {
        struct field
        {
            char name[4];
            char found;
        };

        struct field fields[] = 
        {
            { "byr", 0 },
            { "iyr", 0 },
            { "eyr", 0 },
            { "hgt", 0 },
            { "hcl", 0 },
            { "ecl", 0 },
            { "pid", 0 },
            { "cid", 0 }
        };

        int valid_passports = 0;
        int fields_size = sizeof(fields) / sizeof(struct field);

        char buf[BUFFER_MAX];

        while (1)
        {
            fgets(buf, BUFFER_MAX, fp);

            if (buf[0] == '\n' || feof(fp))
            {
                int valid_fields = 0;

                for (int i = 0; i < fields_size-1; i++)
                {
                    if (fields[i].found)
                    {
                        valid_fields++;
                        fields[i].found = 0;
                    }
                }

                if (valid_fields == fields_size - 1)
                {
                    valid_passports++;
                }
            }
            else
            {
                char* str = strtok(buf, " ");

                while (str != NULL)
                {
                    char field[4];
                    char data[BUFFER_MAX];
                    
                    sscanf(str, "%3s:%s", field, data);
                    
                    for (int i = 0; i < fields_size; i++)
                    {
                        if (!strcmp(field, fields[i].name))
                        {
                            fields[i].found = 1;
                            break;
                        }
                    }

                    str = strtok(NULL, " ");
                }
            }

            if (feof(fp))
            {
                break;
            }
        }

        printf("Valid passports: %d\n", valid_passports);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}