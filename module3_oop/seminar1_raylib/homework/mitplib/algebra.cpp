#include "algebra.hpp"

namespace miptlib
{

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double power(double base, int exponent)
{
    double result = 1.0;

    for (int i = 0; i < exponent; ++i)
    {
        result *= base;
    }

    return result;
}

}
