#include <stdio.h>

struct date
{
    int day, month, year;
};

void print_date(struct date d)
{
    printf("%02i-%02i-%04i\n", d.day, d.month, d.year);
}

struct date pushkin_birthday()
{
    struct date result = {6, 6, 1799};
    return result;
}

int is_winter(struct date d)
{
    return d.month == 12 || d.month == 1 || d.month == 2;
}

struct date next_year(struct date d)
{
    d.year += 1;
    if (d.day == 29 && d.month == 2)
    {
        d.day = 1;
        d.month = 3;
    }
    return d;
}

int main()
{
    struct date a = {10, 5, 2020};

    print_date(a);
    print_date(pushkin_birthday());


    struct date b = {29, 2, 1980};

    printf("a is winter? %i\n", is_winter(a));
    printf("b is winter? %i\n", is_winter(b));

    print_date(next_year(a));
    print_date(next_year(b));
}