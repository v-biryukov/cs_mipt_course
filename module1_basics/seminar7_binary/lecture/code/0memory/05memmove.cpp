/*
    Функция memmove


    Функция memmove делает то же самое, что и функция memcpy, но гарантируется, что она будет работать корректно
    на пересекающихся диапазонах.

    Для этого этой функции нужно сделать проверку на то, что диапазоны пересекаются, поэтому она работает
    чуть-чуть медленнее, чем функция memcpy.
*/

#include <stdio.h>
#include <string.h>

#define SIZE ((size_t)10)

int main()
{
    unsigned char a[SIZE];

    for (size_t i = 0; i < SIZE; ++i)
    {
        a[i] =  (i + 1);
    }


    for (size_t i = 0; i < SIZE; ++i)
    {
        printf("%02hhx ", a[i]);
    }
    printf("\n");



    memcpy(a + 3, a, 6);



    for (size_t i = 0; i < SIZE; ++i)
    {
        printf("%02hhx ", a[i]);
    }
    printf("\n");






    for (size_t i = 0; i < SIZE; ++i)
    {
        a[i] =  (i + 1);
    }



    memmove(a + 3, a, 6);



    for (size_t i = 0; i < SIZE; ++i)
    {
        printf("%02hhx ", a[i]);
    }
    printf("\n");

}