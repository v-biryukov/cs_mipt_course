#include <stdio.h>

#define NUM_ROWS 100
#define NUM_COLS 100


void scan_matrix(int matrix[NUM_ROWS][NUM_COLS], int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            scanf("%i", &matrix[i][j]);
    }
}

void print_matrix(int matrix[NUM_ROWS][NUM_COLS], int n, int m)
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("%i ", matrix[i][j]);

        printf("\n");
    }
}

int sum_matrix(int matrix[NUM_ROWS][NUM_COLS], int n, int m)
{
    int result = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            result += matrix[i][j];
    }

    return result;
}




#include <stdio.h>

int main()
{
    int n, m;
    scanf("%i%i", &n, &m);

    int a[NUM_ROWS][NUM_COLS];
    scan_matrix(a, n, m);

    print_matrix(a, n, m);

    printf("%i\n", sum_matrix(a, n, m));
}
