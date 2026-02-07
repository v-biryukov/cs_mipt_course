#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Animal {
protected:
    std::string mName;
    int mAge;
public:
    Animal(std::string name, int age) : mName(name), mAge(age) {}

    // Теперь метод say -- абстрактный
    virtual void say() const = 0;

    void increaseAge()
    {
        mAge++;
    }

    virtual ~Animal() {};
};

// Класс у которого есть хотя бы один абстрактный метод называется абстрактным
// Нельзя создать экземпляры такого класса. От него нужно только наследоваться


// Класс Bird наследуется от Animal
class Bird : public Animal {
protected:
    int mNumFeathers;
public:
    // Конструктор Bird вызывает конструктор Animal
    Bird(std::string name, int age, int numFeathers) 
        : Animal(name, age), mNumFeathers(numFeathers) {}

    void say() const override
    {
        cout << "<Twittering>" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl; 
        cout << "I have " << mNumFeathers << " feathers!" << endl << endl;
    }

    void pluckFeather()
    {
        mNumFeathers--;
    }
};

// Класс Colibri наследуется от Bird
class Colibri : public Bird {
private:
public:
    // Конструктор Colibri вызывает конструктор Bird
    Colibri(std::string name, int age, int numFeathers) 
        : Bird(name, age, numFeathers) {}

    void say() const override
    {
        cout << "<Colibri Twittering>" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl; 
        cout << "I have " << mNumFeathers << " feathers!" << endl << endl;
    }
};

class Cat : public Animal {
private:
    int mNumMiceCaught;
public:
    // Конструктор Cat вызывает конструктор Animal
    Cat(std::string name, int age, int numMiceCaught) 
        : Animal(name, age), mNumMiceCaught(numMiceCaught) {}

    void say() const override
    {
        cout << "Meow!" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl; 
        cout << "I caught " << mNumMiceCaught << " mouses!" << endl << endl;
    }

    void catchMouse()
    {
        mNumMiceCaught++;
    }
};


class Dog : public Animal
{
private:
    float mBarkingPower;
public:
    // Конструктор Dog вызывает конструктор Animal
    Dog(std::string name, int age, float barkingPower) : Animal(name, age), mBarkingPower(barkingPower)
    {
    }

    void say() const override
    {
        cout << "Woof!" << endl; 
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl << endl; 
        cout << "My barking power = " << mBarkingPower << endl;
    }
};



int main()
{
	// Так как Animal это абстрактный класс, то нельзя создать объект этого класса
    // Animal animal   {"Abstract", 100};


    Bird bird       {"Bubba", 2, 800};
    Colibri colibri {"Coco", 1, 100};
    Cat cat         {"Charlie", 10, 500};
    Dog dog         {"Dante", 20, 90};
    Cat cat2        {"Cleo", 4, 1};


    // Задание 1: Что напечатают следующие строки кода?
    //            Проверьте для случаев когда:
    //            1: ни одна из функций не помечена как virtual
    //            2: только метод say базового класса помечен как virtual
    //            3: только метод say класса Bird помечен как virtual

}