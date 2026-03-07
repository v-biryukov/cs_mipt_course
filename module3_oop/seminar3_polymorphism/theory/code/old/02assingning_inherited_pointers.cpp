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

    void say() const
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
class Bird : public Animal {
private:
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



int main()
{
    Animal animal("Abstract", 100);
    Bird bird("Bubba", 2, 800);

    Animal* pAnimal = &animal;
    Bird* pBird = &bird;

    // Задание:
    // Будет ли работать код ниже и, если да, то что он напечатает?

    // Пример 1: Присваиваем указателю на объект базового класса 
    //           указатель на объект класса наследника
    // pAnimal = pBird;
    // pAnimal->say();

    // Пример 2: Присваиваем указателю на объект класса наследника 
    //           указатель на объект базового класса
    // pBird = pAnimal;
    // pBird->say();

    // Пример 3: Что если воспользуемся приведением типов?
    // pBird = static_cast<Bird*>(pAnimal);
    // pBird->say();
}