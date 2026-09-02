/*
    Тут был использован спецификатор для строки %-30s, который означает, что нужно напечатать не менее
    30 символов, а если символов будет меньше, то нужно добавить пробелов. 
    - означает, что текст нужно выровнять по левому краю.
*/

#include <stdio.h>
#include <string.h>


struct date 
{
    int day, month, year;
};

struct movie 
{
    char title[50];
    int running_time;
    float rating;
    struct date release_date;
};


void print_date(struct date a) 
{
    printf("%02i-%02i-%04i\n", a.day, a.month, a.year);
}

void print_movie(struct movie m) 
{
    printf("%-30s Running time: %3i. Rating: %.2f. Release Date: ", m.title, m.running_time, m.rating);
    print_date(m.release_date);
}


void print_movies(struct movie* movies, size_t n) 
{
    for (size_t i = 0; i < n; ++i)
        print_movie(movies[i]);
}

float average_rating(struct movie array[], size_t n) 
{
    float sum_rating = 0;

    for (int i = 0; i < n; ++i)
        sum_rating += array[i].rating;

    return sum_rating / n;
}


int main() 
{
    struct movie a[10] =   {{"The Godfather", 175, 8.735, {14, 3, 1972}},
                            {"The Shawshank Redemption", 142, 9.112, {10, 9, 1994}},
                            {"Fight Club", 175, 8.651, {10, 9, 1999}},
                            {"The Matrix", 131, 8.491, {24, 3, 1999}},
                            {"Pulp Fiction", 154, 8.620, {19, 5, 1994}},
                            {"Citizen Kane", 119, 7.826, {1, 5, 1941}},
                            {"A Clockwork Orange", 137, 7.959, {19, 12, 1971}},
                            {"2001: A Space Odyssey", 149, 7.988, {2, 4, 1968}},
                            {"Finding Nemo", 175, 7.862, {30, 05, 2003}},
                            {"(500) Days of Summer", 95, 7.6, {17, 1, 2009}}};

    a[4].release_date.day = 21;

    print_movies(a, 10);
    printf("Average rating = %.2f\n", average_rating(a, 10));
}