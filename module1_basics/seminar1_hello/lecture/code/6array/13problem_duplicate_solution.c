#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int a[1000];
    for (int i = 0; i < n; ++i)
        scanf("%i", &a[i]);


    for (int i = 0; i < n; ++i)
        printf("%i %i ", a[i], a[i]);
    printf("\n");
}