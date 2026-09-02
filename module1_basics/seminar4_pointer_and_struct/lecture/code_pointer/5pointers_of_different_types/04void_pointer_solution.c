#include <stdio.h>


int main()
{

    int a[5] = {10, 20, 30, 40, 50};

    void* p = (void*)&a[0];



    for (int i = 0; i < 5; ++i)
        printf("%i ", a[i]);
    printf("\n");

    

    *(int*)p = 100;

    *((int*)p + 3) = 400;



    for (int i = 0; i < 5; ++i)
        printf("%i ", a[i]);
    printf("\n");
        
}
