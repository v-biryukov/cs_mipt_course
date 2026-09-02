/*
    Предыдущее решение можно упростить если использовать функцию max_subarray_index в функции max_subarray.
*/

#include <stdio.h>


int max_subarray_index(int array[], int left, int right)
{
    int max_id = left;
    for (int i = left + 1; i < right; ++i)
    {
        if (array[i] > array[max_id])
            max_id = i;
    }

    return max_id;
}

int max_subarray(int array[], int left, int right)
{
    return array[max_subarray_index(array, left, right)];
}


int main()
{
    int a[10] = {60, 50, 90, 30, 100, 10, 40, 20, 70, 80};

    int x = max_subarray(a, 1, 4);
    int k = max_subarray_index(a, 1, 4);

    printf("%i\n", x);
    printf("%i\n", k);
}