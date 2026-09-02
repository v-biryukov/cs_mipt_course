#include <stdio.h>

int main()
{
    int a[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    int left, right;
    scanf("%i%i", &left, &right);

    // Весь ваш код должен быть расположен тут. Функцию печати менять нельзя.

    for (int i = 0; i < (right - left) / 2; ++i)
    {
        int temp = a[left + i];
        a[left + i] = a[right - 1 - i];
        a[right - 1 - i] = temp;
    }

    // ----------------------------------------------------------------------

    for (int i = 0; i < 10; ++i)
        printf("%i ", a[i]);
    printf("\n");

}