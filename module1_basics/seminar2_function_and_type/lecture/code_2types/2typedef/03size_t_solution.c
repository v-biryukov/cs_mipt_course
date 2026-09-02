#include <stdio.h>

int main()
{
    printf("%zu\n", sizeof(size_t));

    size_t a, b;
    scanf("%zu%zu", &a, &b);

    printf("%zu\n", a * b);
}
