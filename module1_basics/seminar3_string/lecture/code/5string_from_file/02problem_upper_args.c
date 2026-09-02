#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 1000000

void read_file_to_string(const char filename[], char str[])
{
    FILE* f = fopen(filename, "r");
    
    int i = 0;
    while (1)
    {
        int c = fgetc(f);
        if (c == EOF)
            break;

        str[i] = (char)c;
        i += 1;
    }
    str[i] = '\0';

    fclose(f);
}

void save_string_to_file(const char filename[], const char str[])
{
    FILE* f = fopen(filename, "w");
    fprintf(f, "%s", str);
    fclose(f);
}


int main()
{
    char str[BUFFER_SIZE];
    read_file_to_string("three_little_pigs.txt", str);


    save_string_to_file("result.txt", str);
}

/*
    Задача

        Напишите программу upper. Она должна считывать файл, переводить все буквы в верхний регистр и сохранять 
        результат в другой файл. Названия файлов должны передаваться через аргументы командной строки.

        Например, при таком вызове:

            ./upper a.txt b.txt     (Linux)                             .\upper.exe a.txt b.txt     (Windows)         
        
        такая программа должна считывать файл a.txt, переводить все буквы в верхний регистр и записывать в файл b.txt.
        А при таком вызове:

            ./upper three_little_pigs.txt result.txt     (Linux)        .\upper.exe three_little_pigs.txt result.txt     (Windows)

        Программа должна делать то же самое, что и программа из предыдущей задачи.

        Чтобы при компиляции создавался исполняемый файл сразу под названием upper, а не a.out нужно его
        скомпилировать следующей командой:

            gcc -o upper 02problem_upper_args.c

        Программе upper обязательно нужно передавать 2 файла через аргументы командной строки.
        Если аргументов командной строки будет иное количество, то программа должна печатать сообщение об ошибке.
        
        Протестируйте эту программу на текстовых файлах three_little_pigs.txt и invisible_man.txt.
*/