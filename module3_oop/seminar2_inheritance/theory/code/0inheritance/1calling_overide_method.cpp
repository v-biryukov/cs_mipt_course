/*
    Вызов переопределённого метода

    Можно вызвать переопределённый метод из дочернего класса.
    В этом примере в методе say класса Cat вызывается метод say класса Animal.
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
        Animal::say();

        cout << "Meow! My name is " << name << ". "; 
        cout << "I have " << mWhiskersCount << " whiskers!" << endl;
    }
};

int main()
{
    Animal a {"Alice"};
    Cat    c {{"Casper"}, 77};

    c.say();
}



/*
    Задачи:

        1)  Что напечатает данная программа?

*/