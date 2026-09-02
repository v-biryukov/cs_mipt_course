/*
    Функция, принимающая указатель void*.


    Указатель void* может использоваться для передачи некоторого объекта в функцию,
    если мы не знаем тип объекта аргумента на этапе компиляции.


    В данном примере одна и та же функция print используется как для печати объекта типа int,
    так и для печати объекта типа float.
    Сам объект передаётся в функцию по указателю типа void*.

*/

#include <stdio.h>
#include <string.h>

void print(const char* type, void* p)
{
    if (strcmp(type, "int") == 0)
    {
        printf("%i\n", *(int*)p);
    }
    else if (strcmp(type, "float") == 0)
    {
        printf("%f\n", *(float*)p);
    }
    else
    {
        printf("Unknown type\n");
    }
}

int main()
{

    int a = 123;
    float b = 98.76;
    char c = 'K';



    print("int", &a);
    print("float", &b);
    print("char", &c);

}