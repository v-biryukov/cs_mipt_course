/*
    Программа разделена на две единицы трансляции. Для компиляции используйте:

        gcc main.c dynarray.c

*/

#include "dynarray.h"

int main() 
{
    Dynarray a;
    init(&a, 0);
    for (size_t i = 0; i < 100; ++i)
    {
        push_back(&a, i);
    }
    print(&a);
    destroy(&a);
}