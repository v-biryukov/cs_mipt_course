#include <stdio.h>

int main()
{
    int an, am;
    scanf("%i%i", &an, &am);


    int a[100][100];
    for (int i = 0; i < an; ++i)
    {
        for (int j = 0; j < am; ++j)
            scanf("%i", &a[i][j]);
    }


    int b[100][100];
    int bn = am;
    int bm = an;

    for (int i = 0; i < bn; ++i)
    {
        for (int j = 0; j < bm; ++j)
            b[i][j] = a[j][i];
    }

    for (int i = 0; i < bn; ++i)
    {
        for (int j = 0; j < bm; ++j)
            printf("%i ", b[i][j]);

        printf("\n");
    }
}