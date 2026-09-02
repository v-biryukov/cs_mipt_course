#include <stdio.h>


int add(int* pa, int* pb)
{
    return *pa + *pb;
}


int main()
{
    int a = 10;
    int b = 20;


    printf("%i\n", add(&a, &b));
}
