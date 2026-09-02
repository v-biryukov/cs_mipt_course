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

void print_movies(const Movie* movies, size_t n)
{
    for (size_t i = 0; i < n; ++i)
        print_movie(&movies[i]);
}

int main() 
{
    Movie a[10] = 
    {  
        {"The Godfather", 175, 8.735, {14, 3, 1972}},
        {"The Shawshank Redemption", 142, 9.112, {10, 9, 1994}},
        {"Fight Club", 175, 8.651, {10, 9, 1999}},
        {"The Matrix", 131, 8.491, {24, 3, 1999}},
        {"Pulp Fiction", 154, 8.620, {19, 5, 1994}},
        {"Citizen Kane", 119, 7.826, {1, 5, 1941}},
        {"A Clockwork Orange", 137, 7.959, {19, 12, 1971}},
        {"2001: A Space Odyssey", 149, 7.988, {2, 4, 1968}},
        {"Finding Nemo", 175, 7.862, {30, 05, 2003}},
        {"(500) Days of Summer", 95, 7.6, {17, 1, 2009}}
    };

    print_movies(a, 10);
}

/*
    Задача:
        
        Нужно найти самый лучший фильм, то есть фильм с самым высоким рейтингом.
        Причём нужно будет написать 4 функции, каждая из которых будет искать лучший фильм, но возвращать
        результат они должны по разному. В чём преемущества и недостатки каждой из функций?

        1)  Первая функция должна находить лучший фильм и возвращать саму структуру:

                Movie get_best_movie_value(const Movie* movies, size_t n)


        2)  Вторая функция должна находить лучший фильм и возвращать целое число - индекс этой структуры
            во входном массиве:

                size_t get_best_movie_index(const Movie* movies, size_t n)
            

        3)  Третья функция должна находить лучший фильм и возвращать указатель на эту структуру
            во входном массиве:

                const Movie* get_best_movie_pointer(const Movie* movies, size_t n)


        4)  Четвёртая функция тоже должна находить лучший фильм. 
            Эта функция должна принимать на вход массив фильмов, а также некоторый адрес out.
            Функция должна находить лучший фильм и записывать его по адресу out.

                void get_best_movie_address(const Movie* movies, size_t n, Movie* out)


        Вызовите каждую из этих функций из функции main.
        Во всех функциях предполагается, что массив movies содержит хотя бы 1 элемент.
*/