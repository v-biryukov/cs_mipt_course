#include <iostream>
using std::cout;
using std::endl;


class Cat;
class Mouse;


class Cat
{
private:
    int age;
    Mouse* pm;

public:
    Cat(int age, Mouse* pm);
    void say();
};

class Mouse
{
private:
    int age;
    Cat* pc;

public:
    Mouse(int age, Cat* pc);
    void say();
};


Cat::Cat(int age, Mouse* pm) : age(age), pm(pm)
{
}

void Cat::say()
{
    cout << "I am a Cat" << endl;
    if (pm)
    {
        cout << "I caught mouse and it said: " << endl;
        pm->say();
    }
}


Mouse::Mouse(int age, Cat* pc) : age(age), pc(pc)
{
}

void Mouse::say()
{
    cout << "I am a Mouse" << endl;
    if (pc)
    {
        cout << "Cat that caught me said: " << endl;
        pc->say();
    }
}

/*
    Вот теперь всё хорошо.
    Программа скомпилируется.
*/



int main()
{
    Mouse a {5, nullptr};
    Cat b {10, &a};

    b.say();
}