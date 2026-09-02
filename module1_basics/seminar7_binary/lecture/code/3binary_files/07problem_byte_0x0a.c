/*
    Задача:

        Попробуйте догадаться, из каких байт будут состоять получившиеся файлы a_w_mode.bin и a_wb_mode.bin.
        Ответ будет зависеть от вашей операционной системы.
        Разница между файлами будет только на операционной системе Windows.

        Запустите программу и проверьте себя, проанализировав байты получившихся файлов.
        Это можно сделать с помощью утилиты xxd, вот так:

            xxd a_w_mode.bin
*/

#include <stdio.h>


int main()
{
    char a[5] = {0x25, 0x35, 0x0a, 0x40, 0x55};


    FILE* f = fopen("a_w_mode.bin", "w");

    fwrite(&a, sizeof(char), 5, f);

    fclose(f);



    FILE* g = fopen("a_wb_mode.bin", "wb");

    fwrite(&a, sizeof(char), 5, g);

    fclose(g);
}
