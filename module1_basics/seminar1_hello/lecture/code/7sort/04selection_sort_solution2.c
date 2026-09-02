/*
    Нужно поменять условие 

        if (a[i] < a[min_index])    на   if (a[i] > a[max_index])
*/



#include <stdio.h>

int main()
{
    int n;
    scanf("%i", &n);

    int a[1000];
    for (int i = 0; i < n; ++i)
    {
        scanf("%i", &a[i]);
    }


    for (int j = 0; j < n; ++j)
    {
        int max_index = j;
        for (int i = j + 1; i < n; ++i)
        {
            if (a[i] > a[max_index])
                max_index = i;
        }

        int temp = a[j];
        a[j] = a[max_index];
        a[max_index] = temp;
    }



    for (int i = 0; i < n; ++i)
        printf("%i ", a[i]);
    printf("\n");

}


/*
    Задача:

        Измените эту сортировку так, чтобы она сортировала по убыванию последней цифры числа.
        Например, если на вход приходит

            10
            70 11 72 38 93 90 77 46 49 85

        то программа должна напечатать

            49 38 77 46 85 93 72 11 70 90

        так как последние цифры убывают у этих чисел
*/
