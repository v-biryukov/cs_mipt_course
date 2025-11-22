#include <iostream>
#include "get_type_name.hpp"

template<typename T>
void func(T& x)
{
    std::cout << getTypeName<decltype(x)>() << std::endl;
}


int main()
{
    int a = 10;
    func(a);
    func<int&>(a);
    func<const int&>(a);

    std::cout << "---\n";
    const int& b = a;
    func(b);


    std::cout << "---\n";
    int arr[3] = {10, 20, 30};
    func(arr);
}