#include <stdio.h>


void print(int* p)
{
    if (p == NULL)
        printf("Null pointer\n");
    else
        printf("%i\n", *p);
}



int main()
{
    int a = 123;
    

    print(&a);
    print(NULL);


    int* p = NULL;
    print(p);

    p = &a;
    print(p);
}