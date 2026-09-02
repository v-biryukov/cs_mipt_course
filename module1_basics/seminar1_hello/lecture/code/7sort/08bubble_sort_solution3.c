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

    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n - 1 - j; i += 1)
        {
            if (a[i] % 10 > a[i + 1] % 10)
            {
                int temp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = temp;
            }
        }
    }


    for (int i = 0; i < n; ++i)
    {
        printf("%i ", a[i]);
    }
}