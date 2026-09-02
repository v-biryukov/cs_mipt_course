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



    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%i ", 2 * a[i][j]);

        printf("\n");
    }
}


/*
    Для запуска:

        ./a.out < matrix3.txt   (Linux)          a.exe < matrix3.txt   (Windows)
*/