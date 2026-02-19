#include "geometry.hpp"

namespace miptlib
{

static const double pi = 3.141592653589793;

double circleArea(double radius)
{
    return pi * radius * radius;
}

double rectangleArea(double width, double height)
{
    return width * height;
}

double triangleArea(double base, double height)
{
    return 0.5 * base * height;
}

}
