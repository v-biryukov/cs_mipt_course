#include <stdio.h>

#define MACRO(x, y) printf("x = %s\ny = %s\n", #x, #y);
#define DECLARE(t, x, v) t x = v;
#define PI(x) printf("%s = %i\n", #x, x);
#define CONCAT(x, y) x ## y




#define DBG(x) printf("%s = %i\n", #x, x);

int main ()
{
    MACRO(10, 20);
    MACRO(cat, dog);

    DECLARE(int, a, 10);
    
    int CONCAT(cat, dog) = 123;

    DBG(catdog);
}