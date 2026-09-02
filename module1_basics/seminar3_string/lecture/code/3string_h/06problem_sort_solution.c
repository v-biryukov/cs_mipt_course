#include <stdio.h>
#include <string.h>

#define NUM_STRINGS 15
#define BUFFER_SIZE 20


int main() 
{
    char animals[NUM_STRINGS][BUFFER_SIZE] = 
    {
        "Cat", "Dog", "Mouse", "Tiger", "Elephant", "Axolotl", "Monkey",
        "Kangaroo", "Walrus", "Bat", "Orca", "Wolf", "Panda", "Bee", "Hippo"
    };


    for (int i = 0; i < NUM_STRINGS; ++i)
        printf("%s ", animals[i]);
    printf("\n");


    for (int i = 0; i < NUM_STRINGS; ++i) 
    {
        int min_index = i;
        for (int j = i + 1; j < NUM_STRINGS; ++j)
            if (strcmp(animals[j], animals[min_index]) < 0)
                min_index = j;


        char temp[BUFFER_SIZE];
        strcpy(temp, animals[i]);
        strcpy(animals[i], animals[min_index]);
        strcpy(animals[min_index], temp);
    }


    for (int i = 0; i < NUM_STRINGS; ++i)
        printf("%s ", animals[i]);
    printf("\n");

}


/*
    Задачи:

        Напишите функции:

            1)  void print_strings(const char strings[][BUFFER_SIZE], int num_strings) - которая будет печатать на 
                экран массив строк.

            2)  void sort_strings(char strings[][BUFFER_SIZE], int num_strings) - которая будет сортировать массив строк.

        Вызовите эти функции из функции main, чтобы отсортировать массив animals.


*/