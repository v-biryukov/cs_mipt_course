/*
    Сортировка выбором (Selection sort)
*/


#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}


void selection_sort(int array[], int size) 
{
    for (int i = 0; i < size; ++i) 
    {
        int min_index = i;
        for (int j = i + 1; j < size; ++j)
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

    selection_sort(a, 10);
    print_array(a, 10);
}