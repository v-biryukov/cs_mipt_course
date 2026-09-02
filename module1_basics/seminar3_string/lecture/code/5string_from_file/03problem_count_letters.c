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

        Напишите программу count_letters. Она должна считывать файл и считать сколько раз в нём встречается та или 
        иная буква без учёта регистра. Название файла должны передаваться через аргументы командной строки.
        Результат программа должна печатать на экран в следующем формате:

            a:  10
            b:  5
            c:  7
            ...


        Например, при таком вызове:

            ./count_letters three_little_pigs.txt    
        
        Программа должна напечатать:

            a: 80
            b: 25
            c: 36
            d: 72
            e: 162
            f: 50
            g: 41
            h: 119
            i: 128
            j: 2
            k: 13
            l: 84
            m: 28
            n: 97
            o: 100
            p: 42
            q: 0
            r: 46
            s: 53
            t: 138
            u: 43
            v: 6
            w: 33
            x: 3
            y: 24
            z: 0



        Чтобы при компиляции создавался исполняемый файл сразу под названием count_letters, а не a.out нужно его
        скомпилировать следующей командой:

            gcc -o count_letters 03problem_count_letters.c

        Программе upper обязательно нужно передавать файл через аргументы командной строки.
        Если аргументов командной строки будет иное количество, то программа должна печатать сообщение об ошибке.
        Протестируйте эту программу на текстовых файлах three_little_pigs.txt и invisible_man.txt.
*/