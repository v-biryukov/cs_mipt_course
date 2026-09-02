#include <stdio.h>

struct date
{
    int day, month, year;
};

void print_date(struct date d)
{
    printf("%02i-%02i-%04i\n", d.day, d.month, d.year);
}


void print_dates(struct date* dates, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        print_date(dates[i]);
}

int is_later(struct date a, struct date b)
{
    if (a.year != b.year)
        return a.year > b.year;
    if (a.month != b.month)
        return a.month > b.month;
    return a.day > b.day;
}

struct date get_latest_date(struct date* dates, size_t size)
{
    size_t latest_id = 0;
    for (size_t i = 1; i < size; ++i)
    {
        if (is_later(dates[i], dates[latest_id]))
            latest_id = i;
    }
    return dates[latest_id];
}

int main()
{
    struct date holidays[3] = {{31, 12, 2020}, {8, 3, 2020}, {1, 9, 2020}};

    print_dates(holidays, 3);

    printf("Latest date:\n");
    print_date(get_latest_date(holidays, 3));
}