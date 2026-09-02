#include <stdio.h>

struct cat
{
    double b;
    double d;
    double f;
    char a;
    char c;
    char e;
    char g;
};

struct dog
{
    int c;
    short b;
    char a;
    char d;
};


int main()
{
    printf("struct cat size = %zu\n", sizeof(struct cat));
    printf("struct dog size = %zu\n", sizeof(struct dog));
}
