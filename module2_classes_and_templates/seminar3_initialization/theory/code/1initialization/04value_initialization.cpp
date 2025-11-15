/*
    Value initialization (инициализация значением)

    Выглядит вот так:

        type a{};       или так      type a = type();

    Объекты инициализируются так:
    
        1)  Скалярные типы - инициализируются нулями.

        2)  Классы - вызывается конструктор по умолчанию (написанный вами или сгенерированный автоматически).
            Если такого конструктора нет, то это ошибка компиляции.

        3)  Агрегаты - каждый элемент агрегата инициализируется через value initialization.
*/

#include <iostream>
#include <string>
#include "verbose.hpp"
using std::cout, std::endl, std::string;

struct Book
{
    std::string title;
    int pages;
    float price;
};

int main()
{
    int a {};           // скаляр, будет инициализирован нулём

    std::string b {};   // класс, вызовется конструктор по умолчанию, b будет пустой строкой ""

    Book c {};          // агрегат, для c.title вызовется конструктор по умолчанию,
                        //          а c.pages и c.price будут иницализированы нулями

    Verbose d[3] {};    // агрегат, для всех элементов вызовется конструктор по умолчанию


    cout << "a: " << a << endl;
    cout << "b: " <<  b << endl;
    cout << "c.title: " <<  c.title << endl;
    cout << "c.pages: " <<  c.pages << endl;
    cout << "c.price: " <<  c.price << endl;
}

