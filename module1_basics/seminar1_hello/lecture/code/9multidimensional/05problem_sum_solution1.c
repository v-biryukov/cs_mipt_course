#include <stdio.h>

int main()
{
    int n, m;
    scanf("%i%i", &n, &m);


    int a[100][100];
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            scanf("%i", &a[i][j]);
    }


    int sum = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            sum += a[i][j];
    }

    printf("%i\n", sum);
}