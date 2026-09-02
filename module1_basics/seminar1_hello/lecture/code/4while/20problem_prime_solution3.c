/*
    Программу можно ещё ускорить если сначала проверить делимость числа на 2.
    А потом проверять на делимость только на нечётные числа.
*/


#include <stdio.h>

int main() 
{
    int a = 582546791;
    //int a;
    //scanf("%i", &a);

    int is_prime = 1;
    
    if (a % 2 == 0)
    {
        is_prime = 0;
    }
    else
    {
        int i = 3;
        while (i * i <= a)
        {
            if (a % i == 0)
            {
                is_prime = 0;
                break;
            }
            i += 2;
        }
    }

    if (is_prime)
        printf("Prime\n");
    else
        printf("Composite\n");
}