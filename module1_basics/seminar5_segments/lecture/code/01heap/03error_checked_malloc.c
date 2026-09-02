/*
    Если в программе часто вызывается malloc, то нам нужно будет постоянно делать проверки на то, что
    malloc сработал корректно и не вернул NULL. Это может сильно "захламить" код программы.

    Вместо этого можно самим написать функцию, которая будет вызывать malloc и проверять возвращаемое 
    значение malloc. В случае возникновения ошибки эта функция будет её обрабатывать (например, 
    печатать сообщение об ошибки и выходить из программы)
*/

#include <stdlib.h>
#include <stdio.h>

void* error_checked_malloc(size_t n)
{
    void* p = malloc(n);
    if (p == NULL)
    {
        printf("Error. Can't allocate memory!\n");
        exit(1);
    }
    return p;
}

int main()
{
    int* p1 = (int*)error_checked_malloc(sizeof(int));
    // ...
    free(p1);


    float* p2 = (float*)error_checked_malloc(10 * sizeof(float));
    // ...
    free(p2);
}