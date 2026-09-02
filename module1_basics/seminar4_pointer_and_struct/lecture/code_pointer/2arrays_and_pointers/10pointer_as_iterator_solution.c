
#include <stdio.h>

void inc(int* parray, int size)
{
    for (int* p = parray; p < parray + size; ++p)
        *p += 1;
}

int main()
{
    int a[6] = {10, 20, 30, 40, 50, 60};
    
    for (int* p = &a[0]; p - a < 6; ++p)
        printf("%i ", *p);
    printf("\n");

    inc(a, 6);

    for (int* p = &a[0]; p - a < 6; ++p)
        printf("%i ", *p);
    printf("\n");
}