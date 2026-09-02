/*
    Сортировка пузырьком (Bubble sort)
*/


#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}


void bubble_sort(int array[], int size) 
{
    for (int i = 1; i < size; ++i) 
    {
        for (int j = 0; j < size - i; ++j) 
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}


int main()
{
    int a[10] = {60, 50, 90, 30, 100, 10, 40, 20, 70, 80};

    print_array(a, 10);

    bubble_sort(a, 10);
    print_array(a, 10);
}