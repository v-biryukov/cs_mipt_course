/*

    Программу можно сделать более эффективной, если не хранить всю матрицу, а хранить только суммы рядов.
    Нужно поочерёдно считывать все элементы матрицы в переменную temp и прибавлять их к соответствующей сумме ряда.

*/


#include <stdio.h>

int main()
{
    int n, m;
    scanf("%i%i", &n, &m);


    int row_sums[100] = {0};

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            int temp;
            scanf("%i", &temp);

            row_sums[i] += temp;
        }
            
    }


    for (int i = 0; i < n; ++i)
        printf("%i\n", row_sums[i]);
}