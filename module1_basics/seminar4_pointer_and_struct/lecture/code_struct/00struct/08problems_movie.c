#include <stdio.h>
#include <string.h>

int main() 
{

}
/*
    Задачи:

        1)  Описать структуру struct movie с полями:

                - title         - название фильма (строка длиной менне 50 символов).
                - running_time  - длительность в минутах (int)
                - rating        - оценка на Кинопоиске (float)
                - release_date  - дата выхода (используйте структуру struct date из предыдущих заданий).

        2)  Объявить переменную типа struct movie в функции main и инициализировать её следующими значениями:

                title - "Joker", running_time - 122, rating - 7.98, release_date - {3, 10, 2019}.

        3)  В новых строках изменить рейтинг и месяц выхода фильма. Используйте оператор точка.

        4)  Написать функцию void print_movie(struct movie m) и вызвать её в функции main().

        5)  Написать функцию struct movie get_titanic() которая будет возвращать структуру с полями 

                title - "Titanic", running_time - 194, rating - 8.4, release_date - {1, 11, 1997}. 

            Вызовите эту функцию из main и напечатайте результат возвращаемого значения.
*/