#include <stdio.h>

int nearest_integer(float x)
{
    if (x > 0)
        return (int)(x + 0.5);
    else
        return (int)(x - 0.5);
}


int main()
{
    printf("%i\n", nearest_integer(5.4));
    printf("%i\n", nearest_integer(5.6));
    printf("%i\n", nearest_integer(-3.2));
    printf("%i\n", nearest_integer(-3.8));

    printf("%i\n", nearest_integer(0.5));
}
