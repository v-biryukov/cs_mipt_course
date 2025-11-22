#include <iostream>
#include "get_type_name.hpp"
int main()
{
    int a = 10;

    std::cout << getTypeName<int>() << std::endl;
    std::cout << getTypeName<decltype(a)>() << std::endl;
}