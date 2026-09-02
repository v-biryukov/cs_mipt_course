#include <stdio.h>


int max(int array[])
{
    int result = array[0];

    for (int i = 1; i < 10; ++i)
    {
        if (array[i] > result)
            result = array[i];
    }

    return result;
}


int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int b[10] = {50, -20, 20, -80, 10, 80, 20, 40, -90, 70};

    printf("%i\n", max(a));
    printf("%i\n", max(b));
}