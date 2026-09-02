#include <stdio.h>
#include <string.h>

struct date 
{
    int day, month, year;
};
typedef struct date Date;

struct movie 
{
    char title[50];
    int running_time;
    float rating;
    struct date release_date;
};
typedef struct movie Movie;

void print_date(Date d) 
{
    printf("%02i-%02i-%04i", d.day, d.month, d.year);
}

void print_movie(const Movie* pm) 
{
    printf("%-30sRunning time: %4i. Rating: %.2f. Release Date: ", pm->title, pm->running_time, pm->rating);
    print_date(pm->release_date);
    printf("\n");
}

int main() 
{
    Movie a;

    scan_movie(&a);

    print_movie(&a);
}

/*
    Задача:
        
        Напишите функцию scan_movie, которая будет принимать адрес некоторого фильма.
        Эта функция должна считывать фильм с экрана с помощью функции scanf и записывать по этому адресу.

            Movie a;
            scan_movie(&a);
            print_movie(a);

        Каждое поле нужно считать отдельно. Чтобы ввести фильм нужно:

            1)  Ввести название фильма и нажать Enter.
            2)  Ввести длину фильма, его рейтинг и дату выхода через пробел.
                Дату выхода нужно ввести в формате DD-MM-YYYY.

        Например, если мы хотим ввести фильм The Godfather, то нужно написать:

            The Godfather
            175 8.735 14-3-1972
*/