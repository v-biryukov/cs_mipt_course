#include <iostream>
#include <string>
#include <vector>

using std::cout, std::endl;

class Animal 
{
protected:
    std::string mName;
    int mAge;
public:
    Animal(std::string name, int age) : mName(name), mAge(age) {}

    virtual void say() const
    {
        cout << "<abstract sounds>" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl << endl; 
    }

    void increaseAge()
    {
        mAge++;
    }
};


// Класс Bird наследуется от Animal
class Bird : public Animal 
{
protected:
    int mNumFeathers;
public:
    // Конструктор Bird вызывает конструктор Animal
    Bird(std::string name, int age, int numFeathers) 
        : Animal(name, age), mNumFeathers(numFeathers) {}

    void say() const
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
class Colibri : public Bird 
{
private:
public:
    // Конструктор Colibri вызывает конструктор Bird
    Colibri(std::string name, int age, int numFeathers) 
        : Bird(name, age, numFeathers) {}

    void say() const
    {
        cout << "<Colibri Twittering>" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl; 
        cout << "I have " << mNumFeathers << " feathers!" << endl << endl;
    }
};

class Cat : public Animal 
{
private:
    int mNumMiceCaught;
public:
    // Конструктор Cat вызывает конструктор Animal
    Cat(std::string name, int age, int numMiceCaught) 
        : Animal(name, age), mNumMiceCaught(numMiceCaught) {}

    void say() const
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

    void say() const
    {
        cout << "Woof!" << endl; 
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl << endl; 
        cout << "My barking power = " << mBarkingPower << endl;
    }
};



int main()
{
    std::vector<Animal*> animals {
        new Animal  {"Abstract", 100},
        new Bird    {"Bubba", 2, 800},
        new Colibri {"Coco", 1, 100},
        new Cat     {"Charlie", 10, 500},
        new Dog     {"Dante", 20, 90},
        new Cat     {"Cleo", 4, 1}
    };

    // Задание 1: Используйте range-based цикл for, чтобы вызвать метод say для всех объектов

    // Задание 2: Освободите всё память, выделенную с помощью new
}