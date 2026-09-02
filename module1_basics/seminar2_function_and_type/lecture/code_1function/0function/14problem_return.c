/*
    Задача:

        Что напечатает данная программа? Скомпилируйте эту программу, запустите и проверьте ваш ответ.
*/


#include <stdio.h>

int square(int x)
{
    printf("Before return\n");
    return x * x;
    printf("After return\n");
}



int main()
{
    int a = square(5);

    printf("%i\n", square(a));
}


