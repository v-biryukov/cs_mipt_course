#include <stdio.h>
#include <string.h>


int main() 
{
    char animals[15][20] = {"Cat", "Dog", "Mouse", "Tiger", "Elephant", "Axolotl", "Monkey",
                            "Kangaroo", "Walrus", "Bat", "Orca", "Wolf", "Panda", "Bee", "Hippo"};


    for (int i = 0; i < 15; ++i)
        printf("%s ", animals[i]);
    printf("\n");
}


/*
    Задача:
        

        animals - это массив из строк или, что то же самое, двумерный массив символов.
        В массиве animals хранится 15 строк, каждая хранится в массива размером в 20 байт.
        Соответственно, каждая строка может иметь размер не более чем 19 символов. 


        Отсортируйте массив animals по алфавиту.
        Для сортировки можно использовать простую сортировку слиянием.
        Вот, например, сортировка слиянием для чисел типа int:


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


*/