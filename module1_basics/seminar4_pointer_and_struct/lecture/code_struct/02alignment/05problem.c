/*
    Задача:

        Измените порядок полей в структурах, созданных ниже, чтобы уменьшить их размер.
*/

#include <stdio.h>

struct cat
{
    char a;
    double b;
    char c;
    double d;
    char e;
    double f;
    char g;
};

struct dog
{
    char a;
    short b;
    int c;
    char d;
};


int main()
{
    printf("struct cat size = %zu\n", sizeof(struct cat));
    printf("struct dog size = %zu\n", sizeof(struct dog));
}