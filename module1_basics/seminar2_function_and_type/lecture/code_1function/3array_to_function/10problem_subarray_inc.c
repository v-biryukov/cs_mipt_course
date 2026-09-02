/*
    Задача:

        Напишите функцию inc_subarray, которая будет принимать массив и два целых числа left и right
        и будет увеличивать элементы подмассива, задаваемого числами left и right, на 1.

        То есть если есть массив:

            int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

        то после такого вызова:

            inc_subarray(a, 2, 6);

        массив a должен стать таким:

            {10, 20, 31, 41, 51, 61, 70, 80, 90, 100}
*/

#include <stdio.h>

void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
    printf("\n");
}



int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    print_array(a, 10);

    inc_subarray(a, 2, 6);
    print_array(a, 10);

    inc_subarray(a, 0, 10);
    print_array(a, 10);

    inc_subarray(a, 4, 8);
    print_array(a, 10);
}