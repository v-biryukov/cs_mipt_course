/*
    Передача массива в функцию

    Во всех следующих вызовах функций в функцию на самом деле передаётся указатель:

        void func1(int* p)
        void func2(int p[])
        void func2(int p[6])

    То есть p внутри функций во всех этих случаях имеет тип int*
*/

#include <stdio.h>



void func1(int* p)
{
    printf("(1) Size of p = %zu\n", sizeof(p));
}

void func2(int p[])
{
    printf("(2) Size of p = %zu\n", sizeof(p));
}

void func3(int p[6])
{
    printf("(3) Size of p = %zu\n", sizeof(p));
}


int main()
{
    int a[6] = {10, 20, 30, 40, 50, 60};
    printf("(0) Size of a = %zu\n", sizeof(a));
    
    func1(a);
    func2(a);
    func3(a);
}


/*
    Задача:

        Что напечатает программа из данного примера?
*/