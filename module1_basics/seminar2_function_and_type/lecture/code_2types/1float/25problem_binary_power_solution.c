#include <stdio.h>
#include <math.h>

double binpow(double x, unsigned long long n)
{
    if (n == 0) 
    {
        return 1.0;
    }

    if (n % 2 == 1)
    {
        return x * binpow(x, n - 1);
    }
    else
    {
        double temp = binpow(x, n / 2);
        return temp * temp;
    }
}

int main()
{
    printf("%lf\n", binpow(2, 2));
    printf("%lf\n", binpow(2, 16));
    printf("%lf\n", binpow(5.6, 6));


    printf("%le\n", binpow(1.234, 1000));
    printf("%le\n", binpow(0.9995, 10000));
    printf("%le\n", binpow(1.00000000000001, 10000000000000000));
}
