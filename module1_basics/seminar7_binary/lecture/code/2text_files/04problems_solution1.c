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
    int number_of_lines = 0;

    while (1)
    {
        c = fgetc(file);

        if (c == EOF)
            break;

        if (c == '\n')
            number_of_lines += 1;
    }

    number_of_lines += 1; // last line

    printf("Number of lines = %i\n", number_of_lines);
    
    fclose(file);
}