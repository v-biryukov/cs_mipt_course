#include <stdio.h>


void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}


void selection_sort_subarray(int array[], int left, int right) 
{
    for (int i = left; i < right; ++i) 
    {
        int min_index = i;
        for (int j = i + 1; j < right; ++j)
            if (array[j] < array[min_index])
                min_index = j;
        

        int temp = array[i];
        array[i] = array[min_index];
        array[min_index] = temp;
    }
}


int main()
{
    int a[10] = {60, 50, 90, 30, 100, 10, 40, 20, 70, 80};

    print_array(a, 10);

    selection_sort_subarray(a, 2, 6);
    print_array(a, 10);

    selection_sort_subarray(a, 0, 10);
    print_array(a, 10);
}
