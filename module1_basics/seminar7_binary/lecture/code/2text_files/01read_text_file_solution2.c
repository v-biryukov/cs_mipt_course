#include <stdio.h>

int main()
{
    char line[1000];

    FILE* file = fopen("animals.txt", "r");

    fscanf(file, "%999[^\n]", line);
    printf("%s\n", line);

    fclose(file);
}