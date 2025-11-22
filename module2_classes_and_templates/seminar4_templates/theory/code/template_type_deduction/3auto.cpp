#include <iostream>
#include "get_type_name.hpp"

void f(int x) {}


int main()
{
    auto a = 10;
    std::cout << getTypeName<decltype(a)>() << std::endl;

    int& r = a;
    auto b = r;
    std::cout << getTypeName<decltype(b)>() << std::endl;

    const int& cr = a;
    auto c = cr;
    std::cout << getTypeName<decltype(c)>() << std::endl;


    int arr[3] = {10, 20, 30};
    auto d = arr;
    std::cout << getTypeName<decltype(d)>() << std::endl;


    std::cout << "---\n";
    std::cout << getTypeName<decltype(f)>() << std::endl;
    auto e = f;
    std::cout << getTypeName<decltype(e)>() << std::endl;
}