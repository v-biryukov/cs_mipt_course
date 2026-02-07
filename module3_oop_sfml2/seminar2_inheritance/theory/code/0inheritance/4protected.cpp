/*
    Модификатор доступа protected.

    В предыдущих примерах мы использовали публичные поля, чтобы их можно было использовать в дочерних классах
    Так как приватные поля не доступны в дочерних классах.

    Но что если мы хотим использовать сокрытие данных и при наследовании?
    Для этого можно использовать защищённые(protected) поля.
    Такие поля доступны в методах самого класса и методах классов наследников, но не доступны вне класса (кроме друзей).
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
    Animal a {"Alice"};
    Cat    c {"Casper", 77};

    a.say();
    c.say();
}

/*
    Задачи:

        1)  Проверьте, что protected члены недоступны вне методов родительского и дочернего класса.
*/