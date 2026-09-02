#include <stdio.h>


void swap(int* pa, int* pb)
{
    int temp = *pa;
    *pa = *pb;
    *pb = temp;
}

int main()
{
    int a = 10;
    int b = 20;


    printf("%i %i\n", a, b);

    swap(&a, &b);

    printf("%i %i\n", a, b);

}
