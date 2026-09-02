#include <stdio.h>

int main()
{
    for (int i = 32; i <= 126; ++i)
        printf("Symbol = %c, Code = %hhi\n", i, i);
}