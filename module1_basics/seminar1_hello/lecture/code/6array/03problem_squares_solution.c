#include <stdio.h>

int main()
{
    int numbers[20];

    for (int i = 0; i < 20; ++i)
        numbers[i] = i * i;

    for (int i = 0; i < 20; ++i)
        printf("%i ", numbers[i]);
    printf("\n");
}