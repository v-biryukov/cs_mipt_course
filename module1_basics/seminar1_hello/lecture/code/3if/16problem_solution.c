#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);

    if ((a > -100 && a <= -10) || (a >= 10 && a < 100))
        printf("Yes\n");
    else
        printf("No\n");
}