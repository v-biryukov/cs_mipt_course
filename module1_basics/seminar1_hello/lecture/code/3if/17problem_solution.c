#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);

    if (a >= 10 && a < 100 || a % 2 == 0)
        printf("Yes\n");
    else
        printf("No\n");
}
