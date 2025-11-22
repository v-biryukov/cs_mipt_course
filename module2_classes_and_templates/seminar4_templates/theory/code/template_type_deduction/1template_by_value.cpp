#include <iostream>
#include "get_type_name.hpp"

template<typename T>
void func(T x)
{
    std::cout << getTypeName<T>() << std::endl;
}


int main()
{
    int a = 10;
    func(a);
    func<int&>(a);
    func<const int&>(a);

    std::cout << "---\n";
    int& b = a;
    func(b);
    const int& c = a;
    func(c);

    std::cout << "---\n";
    int d[3] = {10, 20, 30};
    func(d);
    func("Hello");
}