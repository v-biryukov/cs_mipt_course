/*
    Наследование

    В данном примере класс Cat наследуется от класса Animal.

    Класс Animal имеет 1 поле name типа std::string. Класс Cat наследует это поле.
    
    У класса Animal есть 2 метода. Класс Cat наследует эти методы.
    Но дочерний класс может переопределить наследуемые методы. В данном примере класс Cat переопределяет метод say.
    Чтобы переопределить метод, нужно написать в дочернем классе метод с такой же сигнатурой, что и метод родительского класса.
    Не нужно путать переопределение метода с перегрузкой. При переопределении метода название метода и его аргументы должны
    полностью совпадать.

*/
#include <iostream>
#include <string>
using std::cout, std::endl;

class Animal 
{
public:
    std::string name;
    void say() const
    {
        cout << "<abstract animal sound>! My name is " << name << "." << endl;
    }
    void jump() const
    {
        cout << name << " jumped!" << endl;
    }
};


class Cat : public Animal
{
public:
    int mWhiskersCount;

    void say() const
    {
        cout << "Meow! My name is " << name << ". "; 
        cout << "I have " << mWhiskersCount << " whiskers!" << endl;
    }
};

int main()
{
    Animal a {"Alice"};
    Cat    c {{"Casper"}, 77};

    a.say();
    c.say();

    a.jump();
    c.jump();

    cout << "Size of Animal = " << sizeof(a) << endl;
    cout << "Size of Cat    = " << sizeof(c) << endl;
}



/*
    Задачи:

        1)  Что напечатает данная программа?

        2)  Что будет если сделать поле name класса Animal приватным?
            Будет ли оно доступно из класса Cat?
*/