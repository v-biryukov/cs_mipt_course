/*
    Функция selection_sort сортирует массив с помощью сортировки выбором.
    Алгоритм сортировки выбором заключается в следующем (size это размер массива):

        Для каждого i от 0 до size - 1 сделаем следующее:

            1)  Найдём индекс минимального элемента на подмассиве [i, size)

            2)  Поменяем местами i-й элемент и минимальный элемент на подмассиве [i, size)

    
    Задачи:
        
        1)  Напишите функцию selection_sort_subarray, которая будет принимать на вход массив и два числа
            left и right и которая будет сортировать подмассив, задаваемый числами left и right с помощью
            сортировки выбора.


        2)  Напишите функцию selection_sort_subarray_rec, которая будет делать то же самое, но рекурсивно.
            Для этого нужно сделать следующее:

                -   Если left >= right то просто выходим из функции

                -   Находим min_index - индекс минимального элемента на подмассиве [left, right) 
                    и меняем местами array[left] и array[min_index]

                -   Рекурсивно сортируем подмассив [left + 1, right)

            Какой из методов более эффективный: с помощью цикла или с помощью рекурсии.
*/


#include <stdio.h>


void print_array(int array[], int size)
{
    for (int i = 0; i < size; ++i)
        printf("%i ", array[i]);
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
