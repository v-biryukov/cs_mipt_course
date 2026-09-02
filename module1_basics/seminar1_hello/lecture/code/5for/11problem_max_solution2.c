/*
    Другой вариант решения этой задачи без использования INT_MAX

    В этом случае мы в переменную max записываем первое из чисел.
    А потом проходим по оставшимся  n - 1  числам.
*/


#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int max;
    scanf("%i", &max);

    for (int i = 2; i <= n; ++i)
    {
        int a;
        scanf("%i", &a);
        
        if (a > max)
            max = a;
    }

    printf("%i\n", max);
}