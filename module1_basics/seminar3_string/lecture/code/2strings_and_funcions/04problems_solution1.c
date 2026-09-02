#include <stdio.h>
#include <ctype.h>

int count_words(const char str[])
{
    int number_of_words = 0;
    int is_prev_space = 1;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (is_prev_space && !isspace(str[i]))
            number_of_words += 1;

        is_prev_space = isspace(str[i]);
    }

    return number_of_words;
}


int main()
{
    char str[201];
    scanf("%200[^\n]", str);

    printf("%i\n", count_words(str));
}