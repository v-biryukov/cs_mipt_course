#include <stdio.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Error. Program should have exactly one command line argument!\n");
        return 1;
    }


    FILE* file = fopen(argv[1], "r");


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