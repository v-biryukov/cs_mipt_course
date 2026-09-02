#include <stdio.h>

int main()
{
    int a[5] = {10, 20, 30, 40, 50};
    int b[5] = {90, 80, 70, 60, 50};

    for (int i = 0; i < 5; ++i)
        a[i] = b[i];

    for (int i = 0; i < 5; ++i)
        printf("%i ", a[i]);
    printf("\n");
}
