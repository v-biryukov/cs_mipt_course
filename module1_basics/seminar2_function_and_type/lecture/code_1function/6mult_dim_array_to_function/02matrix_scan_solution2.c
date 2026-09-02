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

void set_parity_matrix(int matrix[NUM_ROWS][NUM_COLS], int n, int m, int result[NUM_ROWS][NUM_COLS])
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
            result[i][j] = matrix[i][j] % 2;
    }
}




#include <stdio.h>

int main()
{
    int n, m;
    scanf("%i%i", &n, &m);

    int a[NUM_ROWS][NUM_COLS];
    scan_matrix(a, n, m);

    int b[NUM_ROWS][NUM_COLS];

    set_parity_matrix(a, n, m, b);

    print_matrix(a, n, m);
    print_matrix(b, n, m);
}
