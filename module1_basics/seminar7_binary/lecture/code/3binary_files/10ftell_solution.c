#include <stdio.h>


size_t get_file_size(const char* filename)
{
    FILE* f = fopen(filename, "rb");

    fseek(f, 0, SEEK_END);
    size_t result = (size_t)ftell(f);

    fclose(f);

    return result;
}


int main()
{
    printf("%i\n", get_file_size("data.bin"));
    printf("%i\n", get_file_size("10ftell_solution.c"));
}