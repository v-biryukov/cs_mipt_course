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
    printf("%s. Running time: %i. Rating: %.2f. Release Date: ", m.title, m.running_time, m.rating);
    print_date(m.release_date);
}

struct movie get_titanic() 
{
    struct movie result = {"Titanic", 194, 8.4, {1, 11, 1997}};
    return result;
}

int main() 
{
    struct movie a = {"Joker", 122, 7.98, {3, 10, 2019}};
    a.rating += 1;
    a.release_date.month = 11;

    print_movie(a);
    print_movie(get_titanic());
}