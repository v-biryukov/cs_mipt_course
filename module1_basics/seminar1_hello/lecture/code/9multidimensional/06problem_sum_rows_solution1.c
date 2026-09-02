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


    int row_sums[100] = {0};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            row_sums[i] += a[i][j];
    }

    for (int i = 0; i < n; ++i)
        printf("%i\n", row_sums[i]);
}