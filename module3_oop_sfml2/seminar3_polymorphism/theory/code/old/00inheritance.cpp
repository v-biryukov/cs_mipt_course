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

    // Задание:
    // Будет ли работать код ниже и, если да, то что он напечатает?

    // Пример 1: Вызываем метод say базового класса
    // animal.say();

    // Пример 2: Вызываем метод say класса наследника
    // bird.say();

    // Пример 3: Вызываем метод базового класса, используя объект класса наследника
    // bird.increaseAge();
    // bird.say();

    // Пример 4: Вызываем метод say базового класса, используя объект класса наследника
    // bird.Animal::say();



    // Пример 5: Вызываем метод класса наследника, используя объект базового класса
    // animal.pluckFeather();
    // animal.Bird::say();
}