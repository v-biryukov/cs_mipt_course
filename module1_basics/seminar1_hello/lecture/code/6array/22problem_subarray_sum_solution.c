#include <stdio.h>

int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    int left, right;
    scanf("%i%i", &left, &right);


    int sum = 0;
    for (int i = left; i < right; ++i)
        sum += a[i];


    printf("%i\n", sum);
}

