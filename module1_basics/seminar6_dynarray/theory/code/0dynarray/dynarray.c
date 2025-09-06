/*
    Реализация динамического массива, хранящего числа типа int.
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Error checked malloc
void* ecmalloc(size_t n)
{
    void* p = malloc(n);
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    return p;
}

struct dynarray 
{
    int* data;
    size_t size;
    size_t capacity;
};
typedef struct dynarray Dynarray;


void clear(Dynarray* pd)
{
    for (size_t i = 0; i < pd->size; ++i)
        pd->data[i] = 0;
}

void init(Dynarray* pd, size_t initial_size) 
{
    pd->size = initial_size;
    pd->capacity = initial_size;
    if (pd->size == 0)
        pd->data = NULL;
    else
        pd->data = (int*)ecmalloc(pd->capacity * sizeof(int));
    clear(pd);
}

void reserve(Dynarray* pd, size_t new_capacity)
{
    if (new_capacity <= pd->capacity)
        return;

    int* new_data = (int*)ecmalloc(new_capacity * sizeof(int));

    for (size_t i = 0; i < pd->size; ++i)
    {
        new_data[i] = pd->data[i];
    }

    free(pd->data);
    pd->data = new_data;
    pd->capacity = new_capacity;
}


void push_back(Dynarray* pd, int x) 
{
    static const double growth_factor = 2;
    if (pd->size == pd->capacity) 
    {
        size_t new_capacity = (size_t)(growth_factor * pd->capacity);
        
        if (new_capacity <= pd->size)
            new_capacity = pd->size + 1;

        reserve(pd, new_capacity);
    }
    pd->data[pd->size] = x;
    pd->size += 1;
}


int get(const Dynarray* pd, size_t index) 
{
    assert(index >= 0 && index < pd->size);
    return pd->data[index];
}


void set(Dynarray* pd, size_t index, int value) 
{
    assert(index >= 0 && index < pd->size);
    pd->data[index] = value;
}


void print(const Dynarray* pd) 
{
    printf("dynarray: ");
    for (size_t i = 0; i < pd->size; ++i) 
        printf("%i ", pd->data[i]);

    printf("\n");
}


void destroy(Dynarray* pd) 
{
    free(pd->data);
    pd->data = NULL;
}

int main() 
{
    Dynarray a;
    init(&a, 0);
    push_back(&a, 10);
    push_back(&a, 20);
    print(&a);

    set(&a, 0, 50);
    set(&a, 1, 90);
    push_back(&a, 30);
    print(&a);

    printf("%i\n", get(&a, 0));
    
  
    for (size_t i = 0; i < 200; ++i)
    {
        push_back(&a, i);
        printf("address = %p, size = %4i, capacity = %4i\n", a.data, a.size, a.capacity);
    }
    print(&a);
    destroy(&a);
}
