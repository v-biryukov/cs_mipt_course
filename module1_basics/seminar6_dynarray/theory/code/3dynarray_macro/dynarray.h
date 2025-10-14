#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

// Error checked malloc
static void* ecmalloc(size_t n)
{
    void* p = malloc(n);
    if (p == NULL)
    {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }
    return p;
}


#define DECLARE_DYNARRAY(type) \
struct dynarray_##type \
{ \
    type* data; \
    size_t size; \
    size_t capacity; \
}; \
typedef struct dynarray_##type Dynarray_##type; \
\
void dynarray_##type##_clean(Dynarray_##type* pd) \
{ \
    if (pd->data && pd->size > 0)\
        memset(pd->data, 0, pd->size * sizeof(type)); \
} \
 \
void dynarray_##type##_init(Dynarray_##type* pd, size_t initial_size) \
{ \
    pd->size = initial_size; \
    pd->capacity = initial_size; \
    if (pd->size == 0) \
        pd->data = NULL; \
    else \
        pd->data = (type*)ecmalloc(pd->capacity * sizeof(type)); \
    dynarray_##type##_clean(pd); \
} \
 \
void dynarray_##type##_reserve(Dynarray_##type* pd, size_t new_capacity) \
{ \
    if (new_capacity <= pd->capacity) \
        return; \
    type* new_data = (type*)ecmalloc(new_capacity * sizeof(type)); \
    for (size_t i = 0; i < pd->size; ++i) \
    { \
        new_data[i] = pd->data[i]; \
    } \
    free(pd->data); \
    pd->data = new_data; \
    pd->capacity = new_capacity; \
} \
 \
void dynarray_##type##_push_back(Dynarray_##type* pd, type x) \
{ \
    static const double growth_factor = 2; \
    if (pd->size == pd->capacity) \
    { \
        size_t new_capacity = (size_t)(growth_factor * pd->capacity); \
        if (new_capacity <= pd->size) \
            new_capacity = pd->size + 1; \
        dynarray_##type##_reserve(pd, new_capacity); \
    } \
    pd->data[pd->size] = x; \
    pd->size += 1; \
} \
 \
type dynarray_##type##_get(const Dynarray_##type* pd, size_t index)  \
{ \
    assert(index < pd->size); \
    return pd->data[index]; \
} \
 \
void dynarray_##type##_set(Dynarray_##type* pd, size_t index, type value) \
{ \
    assert(index < pd->size); \
    pd->data[index] = value; \
} \
 \
void dynarray_##type##_destroy(Dynarray_##type* pd) \
{ \
    free(pd->data); \
    pd->data = NULL; \
} \

