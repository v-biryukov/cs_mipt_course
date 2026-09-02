#include <stdio.h>


#define ABS(int, a) a > 0 ? a : -a





#define DBG(x) printf("%s = %i\n", #x, x);

int main ()
{
    MACRO(10, 20);
    MACRO(cat, dog);

    DECLARE(int, a, 10);
    
    int CONCAT(cat, dog) = 123;

    DBG(catdog);
}