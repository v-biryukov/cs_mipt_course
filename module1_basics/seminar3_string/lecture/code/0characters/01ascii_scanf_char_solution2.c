#include <stdio.h>

int main()
{
    while (1)
    {
        char a;
        scanf("%c", &a);

        if (a == 113)
            break;

        if (a == 10)
            continue;

        printf("Symbol = %c, Code = %hhi\n", a, a);
    }
}
