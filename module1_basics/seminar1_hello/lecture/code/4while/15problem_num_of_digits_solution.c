#include <stdio.h>

int main()
{
    int a;
    scanf("%i", &a);

    if (a == 0)
    {
        printf("1\n");
    }
    else
    {
        int num = 0;

        while (a > 0)
        {
            num += 1;
            a /= 10;
        }

        printf("%i\n", num);
    }
}
