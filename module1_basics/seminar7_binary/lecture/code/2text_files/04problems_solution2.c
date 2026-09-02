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
    int number_of_letters = 0;
    int number_of_digits = 0;

    while (1)
    {
        c = fgetc(file);

        if (c == EOF)
            break;

        if (isalpha(c))
        {
            number_of_letters += 1;
        }
        else if (isdigit(c))
        {
            number_of_digits += 1;
        }
    }

    printf("Number of letters = %i, number of digits = %i\n", number_of_letters, number_of_digits);
    
    fclose(file);
}