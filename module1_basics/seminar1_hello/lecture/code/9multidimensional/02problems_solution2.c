#include <stdio.h>

int main()
{
    int a[3][3] = {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}};

    for (int i = 0; i < 3; ++i)
        printf("%i ", a[0][i]);
    printf("\n");

}
