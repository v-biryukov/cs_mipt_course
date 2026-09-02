#include <stdio.h>


int main()
{
    FILE* file = fopen("data.bin", "r");

    int byte;

    while (1)
    {
        byte = fgetc(file);

        if (byte == EOF)
            break;

        printf("%02x ", byte);
    }
    printf("\n");


    fclose(file);
}