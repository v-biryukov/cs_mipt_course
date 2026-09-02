#include <stdio.h>

int is_prime(int number)
{
    if (number < 2)
        return 0;

    int result = 1;
    for (int i = 2; i * i <= number; ++i)
    {
        if (number % i == 0)
        {
            result = 0;
            break;
        }
    }
    
    return result;
}


int main() 
{
    int a, b;
    scanf("%i%i", &a, &b);

    for (int number = a; number <= b; ++number)
    {
        if (is_prime(number))
            printf("%i ", number);
    }
    printf("\n");
}