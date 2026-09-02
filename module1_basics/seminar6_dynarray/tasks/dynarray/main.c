/*
    Программа разделена на две единицы трансляции. Для компиляции используйте:

        gcc main.c dynarray.c

    Для тестирования одной функции:

        gcc -DTEST_SHRINK_TO_FIT main.c dynarray.c

    Для тестирования всех функций:

        gcc -DTEST_ALL main.c dynarray.c

*/

#include <stdio.h>
#include "dynarray.h"

int main() 
{
    Dynarray a;
    init(&a, 0);
    for (size_t i = 0; i < 10; ++i)
    {
        push_back(&a, i);
    }
    printf("Initial dynarray: ");
    print(&a);

#if defined(TEST_POP_BACK) || defined(TEST_ALL)

    printf("==================== TEST_POB_BACK ====================\n");
    for (size_t i = 0; i < 3; ++i)
    {
        int result = pop_back(&a);
        printf("Extracted %i\n", result);
    }
    printf("Dynarray after pop_back test: ");
    print(&a);

#endif

#if defined(TEST_RESIZE) || defined(TEST_ALL)

    printf("==================== TEST_RESIZE ====================\n");
    printf("Size and capacity before resize: %zu %zu\n", a.size, a.capacity);
    resize(&a, 3);
    printf("Size and capacity after resize:  %zu %zu\n", a.size, a.capacity);
    printf("Dynarray after resize test: ");
    print(&a);

#endif

#if defined(TEST_SHRINK_TO_FIT) || defined(TEST_ALL)

    printf("==================== TEST_SHRINK_TO_FIT ====================\n");
    printf("Size and capacity before shrink_to_fit: %zu %zu\n", a.size, a.capacity);
    shrink_to_fit(&a);
    printf("Size and capacity after shrink_to_fit:  %zu %zu\n", a.size, a.capacity);
    printf("Dynarray after shrink_to_fit test: ");
    print(&a);

#endif

#if defined(TEST_SHALLOW_COPY) || defined(TEST_ALL)

    printf("==================== TEST_SHALLOW_COPY ====================\n");
    Dynarray b = shallow_copy(&a);
    printf("Dynarray a: ");
    print(&a);

    printf("Dynarray b (shallow copy): ");
    print(&b);

    printf("Adding 10 to all elements of dynarray a:");
    for (size_t i = 0; i < a.size; ++i)
        set(&a, i, get(&a, i) + 10);

    printf("Dynarray a: ");
    print(&a);

    printf("Dynarray b (shallow copy): ");
    print(&b);

#endif

#if defined(TEST_DEEP_COPY) || defined(TEST_ALL)

    printf("==================== TEST_DEEP_COPY ====================\n");
    Dynarray c = deep_copy(&a);
    printf("Dynarray a: ");
    print(&a);

    printf("Dynarray c (deep copy): ");
    print(&c);

    printf("Adding 10 to all elements of dynarray a\n");
    for (size_t i = 0; i < a.size; ++i)
        set(&a, i, get(&a, i) + 10);
    
    printf("Dynarray a: ");
    print(&a);

    printf("Dynarray c (deep copy): ");
    print(&c);

    destroy(&c);

#endif

    destroy(&a);
    printf("Done\n");
}