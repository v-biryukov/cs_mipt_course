/*
    Конструкторы/деструкторы дочерних классов

    Допустим мы хотим создать экземпляр дочернего класса.
    Для того, чтобы создать такой объект, нужно сначала создать объект родительского класса.
    Соответственно, перед вызовом конструктора дочернего класса, всегда будет вызываться конструктор родительского класса.
    В этом примере, при создании объекта типа Cat, сначала будет вызван конструктор класса Animal и уже потом
    будет вызван конструктор класса Cat.

    Если вы не укажите какой конструктор родительского класса нужно вызвать, будет вызван конструктор по умолчанию.
    Чтобы указать какой конструктор родительского класса нужно вызвать, нужно его вызвать в списке инициализации
    дочернего класса, как это проделано вот тут:

        Cat(const std::string& name, int whiskersCount) : Animal{name}, whiskersCount{whiskersCount} 
                                                          ▲
                                                          |
                                             Вызываем конструктор Animal от строки std::string


    Аналогично с деструкторами. При уничтожении объекта дочернего класса, сначала будет вызван деструктор
    дочернего класса, а уже потом деструктор родительского класса.
*/

#include <iostream>
#include <string>
using std::cout, std::endl;

class Animal 
{
public:
    std::string name {"None"};

    Animal()
    {
        cout << "Animal Default Constructor" << endl;
    }

    Animal(const std::string& name) : name{name} 
    {
        cout << "Animal Constructor (" << name << ")" << endl;
    }
    
    void say() const
    {
        cout << "<abstract animal sound>! My name is " << name << "." << endl;
    }
    void jump() const
    {
        cout << name << " jumped!" << endl;
    }

    ~Animal()
    {
        cout << "Animal Destructor (" << name << ")" << endl;
    }
};


class Cat : public Animal
{
public:
    int whiskersCount {0};

    Cat()
    {
        cout << "Cat Default Constructor" << endl;
    }

    Cat(const std::string& name, int whiskersCount) : Animal{name}, whiskersCount{whiskersCount} 
    {
        cout << "Cat Constructor (" << name << ")" << endl;
    }

    void say() const
    {
        cout << "Meow! My name is " << name << ". "; 
        cout << "I have " << whiskersCount << " whiskers!" << endl;
    }

    ~Cat()
    {
        cout << "Cat Destructor (" << name << ")" << endl;
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

        1)  Что напечатает данная программа?
*/