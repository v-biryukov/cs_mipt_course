/*
    Передача двумерного массива в функцию

    Зададим define-константы для размеров матрицы.
*/

#include <stdio.h>

#define NUM_ROWS 3
#define NUM_COLS 3


void inc_matrix(int a[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
            a[i][j] += 1;
    }
}


int main()
{

    int a[NUM_ROWS][NUM_COLS] = {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}};

    inc_matrix(a);

    for (int i = 0; i < NUM_ROWS; ++i)
    {
        for (int j = 0; j < NUM_COLS; ++j)
            printf("%i ", a[i][j]);

        printf("\n");
    }
}