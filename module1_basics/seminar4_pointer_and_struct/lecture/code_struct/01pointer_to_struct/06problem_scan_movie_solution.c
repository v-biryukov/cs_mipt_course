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

void scan_movie(Movie* pm) 
{
    scanf("%[^\n]%i%f%i-%i-%i", pm->title, &pm->running_time, &pm->rating, 
        &pm->release_date.day, &pm->release_date.month, &pm->release_date.year);
}

int main() 
{
    Movie a;

    scan_movie(&a);

    print_movie(&a);
}