#include <stdio.h>

int main()
{
    FILE* file = fopen("animals.txt", "r");


    int c;

    while (1)
    {
        c = fgetc(file);

        if (c == EOF)
            break;

        printf("%c", (char)c);
    }

    fclose(file);
}