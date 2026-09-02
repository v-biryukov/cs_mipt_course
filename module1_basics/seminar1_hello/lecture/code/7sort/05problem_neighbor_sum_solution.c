/*
    Просто нужно напечатать a[i] + a[i + 1] для всех i от 0 до n - 2.
    Поэтому условие будет   i < n - 1

    Первая сумма это      a[0] + a[1]
    Последняя сумма это   a[n - 2] + a[n - 1]
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

    for (int i = 0; i < n - 1; ++i) 
    {
        printf("%i ", a[i] + a[i + 1]);
    }
    printf("\n");

}