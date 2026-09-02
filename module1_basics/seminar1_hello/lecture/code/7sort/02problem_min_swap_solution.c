#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int a[1000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
    }

    int min_index = 0;

    for (int i = 0; i < n; ++i)
    {
        if (a[i] < a[min_index])
            min_index = i;
    }

    int temp = a[0];
    a[0] = a[min_index];
    a[min_index] = temp;

    for (int i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");

}