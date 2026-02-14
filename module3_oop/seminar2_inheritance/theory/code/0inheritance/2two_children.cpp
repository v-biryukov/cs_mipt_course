/*
    Наследование

    От одного класса могут наследоваться множество других классов.
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
    int whiskersCount;

    void say() const
    {
        cout << "Meow! My name is " << name << ". "; 
        cout << "I have " << whiskersCount << " whiskers!" << endl;
    }
};


class Dog : public Animal
{
public:
    int barkingPower;

    void say() const
    {
        cout << "Meow! My name is " << name << ". ";
        cout << "My barking power is " << barkingPower << "!" << endl;
    }
};

int main()
{
    Animal a {"Alice"};
    Cat    c {{"Casper"}, 77};
    Dog    d {{"Daisy"}, 10};

    a.say();
    c.say();
    d.say();

    a.jump();
    c.jump();
    d.jump();
}


/*
    Задачи:

        1)  Что напечатает данная программа?
*/