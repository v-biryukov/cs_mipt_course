#include <stdio.h>

int main()
{
    int a[3][3] = {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}};

    int sum = 0;

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
            sum += a[i][j];
    }

    printf("%i\n", sum);

}