#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::endl;


class Base {
protected:
    double a;

public:
    Base(double a) : a(a) {}

    /*virtual*/ void print()
    {
        cout << "(" << a << ")" << endl;
    }
};


class Derived : public Base{
public:
    Derived(double a) : Base(a) {}

    void print()
    {
        cout << "[" << a << "]" << endl;
    }
};

int main()
{
    Derived d {5};

    Base* p = &d;

    // Что напечатает следующие строки в случае если метод базового класса является
    // обычным и виртуальным

    // Пример 1:
    // p->print();

    // Пример 2:
    // cout << sizeof(Base) << endl;

    // Пример 3:
    // cout << sizeof(Derived) << endl;
}