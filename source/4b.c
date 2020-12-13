#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 256

int byrValid(char* str)
{
    // Four digits; at least 1920 and at most 2002
    if (strlen(str) != 4)
    {
        return 0;
    }

    int year = atoi(str);
    
    if (year < 1920 || year > 2002)
    {
        return 0;
    }

    return 1;
}

int iyrValid(char* str)
{
    // Four digits; at least 2010 and at most 2020
    if (strlen(str) != 4)
    {
        return 0;
    }

    int year = atoi(str);
    
    if (year < 2010 || year > 2020)
    {
        return 0;
    }

    return 1;
}

int eyrValid(char* str)
{
    // Four digits: at least 2020 and at most 2030
    if (strlen(str) != 4)
    {
        return 0;
    }

    int year = atoi(str);

    if (year < 2020 || year > 2030)
    {
        return 0;
    }

    return 1;
}

int hgtValid(char* str)
{
    // Either cm or in:
    // - cm: at least 150 and at most 193
    // - in: at least 59 and at most 76
    if (strlen(str) < 2)
    {
        return 0;
    }

    char* type = &str[strlen(str)-2];

    if (!strcmp(type, "cm"))
    {
        int height;
        sscanf(str, "%dcm", &height);

        if (height >= 150 && height <= 193)
        {
            return 1;
        }
    }
    else if (!strcmp(type, "in"))
    {
        int height;
        sscanf(str, "%din", &height);

        if (height >= 59 && height <= 76)
        {
            return 1;
        }
    }

    return 0;
}

int hclValid(char* str)
{
    // A # followed by exactly six characters, 0-9 or a-f
    if (str[0] != '#' || strlen(str) != 7)
    {
        return 0;
    }

    for (int i = 1; i < 7; i++)
    {
        if ((str[i] < '0' || str[i] > '9') && (str[i] < 'a' || str[i] > 'f'))
        {
            return 0;
        }
    }

    return 1;
}

int eclValid(char* str)
{
    // One of amb, blu, brn, gry, grn, hzl or oth
    char colors[][4] = { "amb", "blu", "brn", "gry", "grn", "hzl", "oth" };
    int colors_size = sizeof(colors) / 3;

    for (int i = 0; i < colors_size; i++)
    {
        if (!strcmp(str, colors[i]))
        {
            return 1;
        }
    }

    return 0;
}

int pidValid(char* str)
{
    // Nine-digit number, including leading zeroes
    if (strlen(str) != 9)
    {
        return 0;
    }

    for (int i = 0; i < 9; i++)
    {
        if (str[i] < '0' || str[i] > '9')
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/4.txt", "r");

    if (fp)
    {
        struct field
        {
            char name[4];
            char found;
            int (*isValid)(char*);
        };

        struct field fields[] = 
        {
            { "byr", 0, byrValid },
            { "iyr", 0, iyrValid },
            { "eyr", 0 ,eyrValid },
            { "hgt", 0, hgtValid },
            { "hcl", 0, hclValid },
            { "ecl", 0, eclValid },
            { "pid", 0, pidValid }
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

                for (int i = 0; i < fields_size; i++)
                {
                    if (fields[i].found)
                    {
                        valid_fields++;
                        fields[i].found = 0;
                    }
                }

                if (valid_fields == fields_size)
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
                        if (!strcmp(field, fields[i].name) && 
                            fields[i].isValid(data))
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