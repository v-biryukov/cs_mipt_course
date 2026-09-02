#include <stdio.h>


int sum_subarray_rec(int array[], int left, int right)
{
    if (left >= right)
        return 0;

    return array[left] + sum_subarray_rec(array, left + 1, right);
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    printf("%i\n", sum_subarray_rec(a, 2, 6));

    printf("%i\n", sum_subarray_rec(a, 0, 10));

    printf("%i\n", sum_subarray_rec(a, 0, 1));
}
