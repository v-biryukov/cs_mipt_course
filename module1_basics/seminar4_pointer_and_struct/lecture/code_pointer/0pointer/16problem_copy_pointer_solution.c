#include <stdio.h>


int main()
{
    int a = 10;
    int* p = &a;

    printf("a = %i\n", a);
    printf("p = %p\n", p);

    printf("address of a = %p\n", &a);
    printf("address of p = %p\n", &p);




    int* q = p;
    printf("q = %p\n", q);

}

/*
    Решение:

        Когда мы пишем так:
        
            int* q = p;

        То мы создаём переменную, которая будет равна переменной p.
        То есть q будет хранить в себе абсолютно такое же значение, что и переменная p.

        Так как p хранит адрес a, то и q будет хранить адрес a.
*/
