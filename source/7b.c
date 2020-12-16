#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_MAX 256
#define BAGS_MAX   16

struct bag
{
    char name[BUFFER_MAX];
    struct bag* bags[BAGS_MAX];
    int counts[BAGS_MAX];
    int bag_count;
};

struct bag* bag_get(struct bag* bags, int* bags_count, char* bag_name)
{
    for (int i = 0; i < *bags_count; i++)
    {
        if (!strcmp(bag_name, bags[i].name))
        {
            return &bags[i];
        }
    }

    strcpy(bags[*bags_count].name, bag_name);

    return &bags[(*bags_count)++];
}

void bag_name_get(char* src, char* dest)
{
    strncpy(dest, src, strstr(src, "bag")-src-1);
}

int bag_has_bag(struct bag* a, struct bag* b)
{
    for (int i = 0; i < a->bag_count; i++)
    {
        if (a->bags[i] == b || bag_has_bag(a->bags[i], b))
        {
            return 1;
        }
    }

    return 0;
}

int bags_calculate(struct bag* bag)
{
    int result = 0;

    for (int i = 0; i < bag->bag_count; i++)
    {
        result += bags_calculate(bag->bags[i]) * bag->counts[i] + 
            bag->counts[i];
    }

    return result;
}

int main(int argc, char** argv)
{
    FILE* fp = fopen("../data/7.txt", "r");

    if (fp)
    {
        char buf[BUFFER_MAX];
        int rows = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            rows++;
        }

        printf("Number of rows in input file: %d\n", rows);

        struct bag* bags = malloc(sizeof(struct bag) * rows);

        memset(bags, 0, sizeof(struct bag) * rows);

        int bags_count = 0;
        rewind(fp);

        struct bag* shiny_gold_bag = 0;

        while (fgets(buf, BUFFER_MAX, fp))
        {
            char name[BUFFER_MAX] = {0};

            bag_name_get(buf, name);

            struct bag* bag = bag_get(bags, &bags_count, name);

            if (!strcmp(name, "shiny gold"))
            {
                shiny_gold_bag = bag;
            }

            char* bag_list = buf + 
                (strstr(buf, "contain") - buf + strlen("contain "));

            if (strncmp(bag_list, "no", 2))
            {
                char* str = strtok(bag_list, ",");

                while(str != NULL)
                {
                    char temp_name[BUFFER_MAX] = {0}; 

                    sscanf(str, "%d", &bag->counts[bag->bag_count]);

                    bag_name_get(str+(str[0] == ' ' ? 3 : 2), temp_name);

                    bag->bags[bag->bag_count++] = bag_get(bags, 
                        &bags_count, temp_name);

                    str = strtok(NULL, ",");
                }
            }

        }

        for (int i = 0; i < bags_count; i++)
        {
            printf("%s: ", bags[i].name);

            for (int j = 0; j < bags[i].bag_count; j++)
            {
                printf("%d %s, ", bags[i].counts[j], bags[i].bags[j]->name);
            }
            printf("\n");
        }

        int count = bags_calculate(shiny_gold_bag);

        printf("Total: %d\n", count);
    }
    else
    {
        printf("file not found\n");
    }

    return 0;
}