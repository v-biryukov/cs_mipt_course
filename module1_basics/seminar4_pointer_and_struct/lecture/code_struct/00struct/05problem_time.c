/*
    Задача:

        Программист, который не знает, что такое структуры, написал следующий код.
        В этом коде мы для описания момента времени используем 3 переменных типа int.

        -   Функция print_time печатает время на экран.

        -   Функция total_seconds возвращает общее количество секунд в этом времени.

        -   Функция sum_time вычисляет сумму двух времен. Так как мы не можем вернуть сразу 3 значения,
            то результат суммы записывается по адресам res_hours, res_minutes и res_seconds.


        Перепишите этот код с использованием структур.
        При этом измените функцию sum_time так, чтобы она возвращала структуру, а не записывала результат
        по какому-либо адресу.
*/

#include <stdio.h>

void print_time(int hours, int minutes, int seconds)
{
    printf("%02i:%02i:%02i\n", hours, minutes, seconds);
}

int total_seconds(int hours, int minutes, int seconds)
{
    return 3600 * hours + 60 * minutes + seconds;
}

void sum_time(int hours1, int minutes1, int seconds1, int hours2, int minutes2, int seconds2, int* res_hours, int* res_minutes, int* res_seconds)
{
    int total = total_seconds(hours1, minutes1, seconds1) + total_seconds(hours2, minutes2, seconds2);

    *res_hours = total / 3600;
    *res_minutes = (total % 3600) / 60;
    *res_seconds = total % 60;
}


int main()
{
    int h1 = 9;
    int m1 = 5;
    int s1 = 25;

    int h2 = 12;
    int m2 = 55;
    int s2 = 40;

    print_time(h1, m1, s1);
    print_time(h2, m2, s2);


    int h3, m3, s3;
    sum_time(h1, m1, s1, h2, m2, s2, &h3, &m3, &s3);
    print_time(h3, m3, s3);
}