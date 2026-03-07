#include <iostream>
#include <string>

using std::cout;
using std::endl;

// Интерфейс -- это класс у которого нет полей и все его методы абстрактные
class IAnimal {
public:
    virtual void say() const = 0;
    virtual void move() const = 0;
    virtual void sleep() const = 0;

    virtual ~IAnimal() {};
};

// Объекты такого класса нельзя создать, от него нужно наследоваться
// Все классы, которые наследуются от интерфейса обязаны переопределить
// все абстрактные методы интерфейса



// Класс Bird наследуется от IAnimal
class Bird : public IAnimal {
protected:
    int mNumFeathers;
public:
    Bird(int numFeathers) : mNumFeathers(numFeathers) {}

    void say() const
    {
        cout << "<Twittering>" << endl;
    }

    void move() const
    {
        cout << "Flying using my " << mNumFeathers << " feathers" << endl;
    }
    
    void sleep() const
    {
        cout << "zzzZZZzzz" << endl;
    }
};

class Cat : public IAnimal {
private:
    int mNumMiceCaught;
public:
    Cat(int numMiceCaught) : mNumMiceCaught(numMiceCaught) {}

    void say() const
    {
        cout << "Meow!" << endl;
    }

    void move() const
    {
        cout << "Walking" << endl;
    }
    
    void sleep() const
    {
        cout << "zzzZZZzzz I caught " << mNumMiceCaught << " mice today" << endl;
    }
};

int main()
{
    Bird bird {800};
    Cat cat   {500};
    Cat cat2  {1};

    // Задание 1: Что напечатают следующие строки кода?
    // IAnimal* p = &bird;
    // p->move();

    // Задание 2: Что будет, если не переопределять один из методов?

    // Задание 3: Можно ли сделать деструктор класса IAnimal не виртуальным?
}