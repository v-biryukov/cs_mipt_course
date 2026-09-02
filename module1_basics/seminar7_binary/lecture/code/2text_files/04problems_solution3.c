#include <stdio.h>
#include <ctype.h>

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        printf("Error. Program should have exactly one command line argument!\n");
        return 1;
    }

    FILE* file = fopen(argv[1], "r");


    int c;
    int number_of_words = 0;

    int is_prev_space = 1;
    int is_current_space = 1;

    while (1)
    {
        c = fgetc(file);

        if (c == EOF)
            break;

        is_prev_space = is_current_space;
        is_current_space = isspace(c);

        if (is_prev_space && !is_current_space)
            number_of_words += 1;
    }

    printf("Number of words = %i\n", number_of_words);
    
    fclose(file);
}