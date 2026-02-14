/*
    Присваивание объекта дочернего класса к объекту родительского

    Можно присваивать объекты дочернего класса к объектам родительского класса.
    Так как объект дочернего класса содержит внутри себя объект родительского.
    При этом будет производится срезка объекта (object slicing)

    Например, в этом примере можно написать a = c, но поле mWhiskersCount объекта c
    не будет скопировано, так как в объекте a просто нет места под это поле.
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


int main()
{
    {
        Animal a {"Alice"};
        Cat    c {"Casper", 77};

        // Будет ли работать код ниже и, если да, то что он напечатает?
        // c = a;
        // c.say();
    }


    {
        Animal a {"Alice"};
        Cat    c {"Casper", 77};

        // Будет ли работать код ниже и, если да, то что он напечатает?
        // a = c;
        // a.say();
    }
}