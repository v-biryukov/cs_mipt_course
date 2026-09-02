#include <stdio.h>

int main()
{
    char str[20] = "Cats and dogs";

    for (int i = 0; str[i] != '\0'; ++i)
        printf("%c", str[i]);
    printf("\n");


    for (int i = 0; str[i]; ++i)
        printf("%c", str[i]);
    printf("\n");


}

/*
    Представлено 2 решения
*/