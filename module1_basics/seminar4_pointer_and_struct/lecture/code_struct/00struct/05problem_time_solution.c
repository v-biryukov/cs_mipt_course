#include <stdio.h>

struct time
{
    int hours, minutes, seconds;
};

void print_time(struct time t)
{
    printf("%02i:%02i:%02i\n", t.hours, t.minutes, t.seconds);
}

int total_seconds(struct time t)
{
    return 3600 * t.hours + 60 * t.minutes + t.seconds;
}

struct time sum_time(struct time t1, struct time t2)
{
    int total = total_seconds(t1) + total_seconds(t2);
    struct time result = {total / 3600, (total % 3600) / 60, total % 60};
    return result;
}

int main()
{
    struct time t1 = {9, 5, 25};
    struct time t2 = {12, 55, 40};

    print_time(t1);
    print_time(t2);

    struct time t3 = sum_time(t1, t2);
    print_time(t3);
}