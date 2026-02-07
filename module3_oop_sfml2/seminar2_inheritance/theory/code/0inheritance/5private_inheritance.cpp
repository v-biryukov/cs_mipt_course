/*
    Публичное и приватное наследование

    Можно указать тип наследования: публичное или приватное.
    В данном примере класс Cat наследуется от класса Animal публично,а класс Dog наследуется от класса Animal приватно.

        class Cat : public Animal
        class Dog : private Animal

    Разница в том, что при публичном наследовании public/protected члены класса Animal остаются public/protected в дочернем классе.
    При приватном наследовании public/protected члены класса Animal становятся приватными в дочернем классе.
*/

#include <iostream>
#include <string>
using std::cout, std::endl;

class Animal 
{
protected:
    std::string mName {"None"};

public:
    Animal() {}
    Animal(const std::string& name) : mName{name} {}
    
    void say() const
    {
        cout << "<abstract animal sound>! My name is " << mName << "." << endl;
    }
    void jump() const
    {
        cout << mName << " jumped!" << endl;
    }
};


class Cat : public Animal
{
protected:
    int mWhiskersCount {0};

public:
    Cat() {}
    Cat(const std::string& name, int whiskersCount) : Animal{name}, mWhiskersCount{whiskersCount} {}

    void say() const
    {
        cout << "Meow! My name is " << mName << ". "; 
        cout << "I have " << mWhiskersCount << " whiskers!" << endl;
    }
};



class Dog : private Animal
{
protected:
    int mBarkingPower {0};

public:
    Dog() {}
    Dog(const std::string& name, int barkingPower) : Animal{name}, mBarkingPower{barkingPower} {}

    void say() const
    {
        cout << "Woof! My name is " << mName << ". "; 
        cout << "My barking power is " << mBarkingPower << " decibels!" << endl;
    }
};

int main()
{
    Animal a {"Alice"};
    Cat    c {"Casper", 77};
    Dog    d {"Daisy", 10};

    a.say();
    c.say();
    d.say();

    a.jump();
    c.jump();
    // d.jump();
}



/*
    Задачи:

        1)  Можно ли вызвать метод jump класса Dog в функции main?

        2)  Можно ли вызвать метод jump класса Dog в методе say класса Dog?
*/