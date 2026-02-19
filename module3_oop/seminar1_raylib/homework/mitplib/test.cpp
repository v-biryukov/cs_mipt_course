#include <iostream>
#include <vector>

#include "miptlib.hpp"

int main()
{
    std::cout << miptlib::add(3, 4) << std::endl;
    std::cout << miptlib::power(2, 5) << std::endl;
    std::cout << miptlib::circleArea(5) << std::endl;

    std::vector<double> data = {1, 2, 3, 4, 5};

    std::cout << miptlib::mean(data) << std::endl;
}