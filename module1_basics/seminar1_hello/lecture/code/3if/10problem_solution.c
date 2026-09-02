#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);

    if (a % 10)
        printf("Not round\n");
    else
        printf("Round\n");
}
