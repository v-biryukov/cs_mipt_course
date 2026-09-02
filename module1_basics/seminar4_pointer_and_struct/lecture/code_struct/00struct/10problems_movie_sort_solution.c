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

void sort_movies_by_rating(struct movie* array, int n) 
{
    for (int j = 0; j < n; j++)
    {
        int min_index = j;
        for (int i = j + 1; i < n; i++) 
        {
            if (array[i].rating > array[min_index].rating)
                min_index = i;
        }

        struct movie temp = array[j];
        array[j] = array[min_index];
        array[min_index] = temp;
    }
}


void sort_movies_by_title(struct movie* array, int n) 
{
    for (int j = 0; j < n; j++)
    {
        int min_index = j;
        for (int i = j + 1; i < n; i++) 
        {
            if (strcmp(array[i].title, array[min_index].title) < 0)
                min_index = i;
        }

        struct movie temp = array[j];
        array[j] = array[min_index];
        array[min_index] = temp;
    }
}


int main() 
{
    struct movie a[10] =   
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

    printf("Initial array of movies:\n");
    print_movies(a, 10);

    printf("\nSorted by rating:\n");
    sort_movies_by_rating(a, 10);
    print_movies(a, 10);

    printf("\nSorted by title:\n");
    sort_movies_by_title(a, 10);
    print_movies(a, 10);
}