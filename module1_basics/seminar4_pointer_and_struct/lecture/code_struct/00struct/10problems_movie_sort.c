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

    print_movies(a, 10);
}

/*
    Сортировка структур

    Одна из простейших сортировок - это сортировка выбором.
    Вот пример сортировки выбором, которая сортирует массив целых чисел типа int.

        void selection_sort(int* array, int n) 
        {
            for (int j = 0; j < n; j++)
            {
                // Находим индекс минимального элемента на отрезке [j:n-1]
                int min_index = j;
                for (int i = j + 1; i < n; i++) 
                {
                    if (array[i] < array[min_index])
                        min_index = i;
                }

                // Меняем местами элемент номер j и минимальный элемент
                int temp = array[j];
                array[j] = array[min_index];
                array[min_index] = temp;
            }
        }

    Задачи:

        1)  Видоизмените эту сортировку так, чтобы она сортировала фильмы по рейтингу (от большего к меньшему).
            Назовите эту функцию как sort_movies_by_rating.
            Протестируйте эту функцию на массиве a из функции main.
            Помните, что структуры можно присваивать целиком, а не поэлементно.

        2)  Напишите функцию sort_movies_by_title, которая будет сортировать фильмы по их названию в алфавитном порядке.
            Используйте функцию strcmp из string.h. Функция strcmp(a, b) возращает 0, если строки равны, отрицательное
            число если строка a меньше, чем строка b и положительное число, если строка a больше, чем b.
            Протестируйте эту функцию на массиве a из функции main.
*/