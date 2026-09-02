/*
    Нужно поменять условие 

        if (a[i] > a[max_index])    на    if (a[i] % 10 > a[max_index] % 10)
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
            if (a[i] % 10 > a[max_index] % 10)
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
