/*
    Изменить величину выравнивания, используя атрибуты

    Выравнивание можно настроить, используя атрибуты packed и aligned компилятора gcc.

        aligned -   устанавливает выравнивание.
        packed  -   упаковывает поля так, чтобы между полями одной структуры не было промежутков.

    !!  Атрибуты __attribute__ не являются частью стандарта!
        Они будут работать на компиляторе gcc, но вероятно не будут работать на других компиляторов.
*/


#include <stdio.h>

struct cat 
{
    char a;
    double b;
    char c;
};


struct __attribute__((packed))  dog 
{
    char a;
    double b;
    char c;
};


struct __attribute__((packed, aligned(8)))  mouse 
{
    char a;
    double b;
    char c;
};



int main()
{
    printf("%zu\n", sizeof(struct cat));
    printf("%zu\n", sizeof(struct dog));
    printf("%zu\n", sizeof(struct mouse));
}