#include <stdio.h>
#include <string.h>

#define SIZE ((size_t)100)

int main()
{
    unsigned char a[SIZE];

    memset(a, 0xe3, SIZE / 2);
    memset(a + SIZE / 2, 0xf4, SIZE - SIZE / 2);


    for (size_t i = 0; i < SIZE; ++i)
    {
        printf("%hhx ", a[i]);
    }
    printf("\n");

}