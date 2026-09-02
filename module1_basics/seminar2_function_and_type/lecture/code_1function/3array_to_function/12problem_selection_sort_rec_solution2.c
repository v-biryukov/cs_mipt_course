#include <stdio.h>


void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}


void selection_sort_subarray_rec(int array[], int left, int right) 
{
    if (left >= right)
        return;

    int min_index = left;
    for (int j = left + 1; j < right; ++j)
        if (array[j] < array[min_index])
            min_index = j;
    

    int temp = array[left];
    array[left] = array[min_index];
    array[min_index] = temp;

    selection_sort_subarray_rec(array, left + 1, right);
}


int main()
{
    int a[10] = {60, 50, 90, 30, 100, 10, 40, 20, 70, 80};

    print_array(a, 10);

    selection_sort_subarray_rec(a, 2, 6);
    print_array(a, 10);

    selection_sort_subarray_rec(a, 0, 10);
    print_array(a, 10);
}


/*
    Метод с использованием цикла более эффективен, чем метод с использованием рекурсии.

    В будущем мы пройдём более сложные алгоритмы, где рекурсия примерно также эффективна как и цикл 
    и при этом позволяет записывать алгоритм гораздо более компакто.
    Например, алгоритмы быстрой сортировки и сортировки слиянием.
*/