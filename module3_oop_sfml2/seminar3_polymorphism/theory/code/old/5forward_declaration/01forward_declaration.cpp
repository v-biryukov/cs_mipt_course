#include <iostream>
using std::cout;
using std::endl;

class Mouse;

class Cat
{
private:
    int age;
    Mouse* pm;

public:
    Cat(int age, Mouse* pm) : age(age), pm(pm)
    {
    }

    void say()
    {
        cout << "I am a Cat" << endl;
        if (pm)
        {
            cout << "I caught mouse and it said: " << endl;
            pm->say();
        }
    }
};


class Mouse
{
private:
    int age;
    Cat* pc;

public:
    Mouse(int age, Cat* pc) : age(age), pc(pc)
    {
    }

    void say()
    {
        cout << "I am a Mouse" << endl;
        if (pc)
        {
            cout << "Cat that caught me said: " << endl;
            pc->say();
        }
    }
};


/*
    Данная программа не скомпилируется, так как на момент определения класса Cat нужно
    знать класс Mouse и метод Mouse::say().
    Всё должно быть определено до использования, поэтому программа не скомпилируется.
*/


int main()
{
    Mouse a {5, nullptr};
    Cat b {10, &a};

    b.say();
}