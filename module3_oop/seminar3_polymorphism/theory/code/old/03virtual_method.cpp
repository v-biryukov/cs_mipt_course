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

    // Этот метод по заданию нужно будет сделать виртуальным
    // Заменить void say() на virtual void say()
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

    
    Animal* p = &bird;
    Animal* q = &cat;
    p->say();
    q->say();


    
    // Задание 1: Присваиваем объект базового класса объекту класса наследника
    // Какой метод say вызовется?

    // animal = bird;
    // animal.say();
    Animal* pAnimal = &animal;
    Bird* pBird = &bird;


    // Задание 2: Присваиваем указателю на объект базового класса 
    //           указатель на объект класса наследника
    // Какой метод say вызовется?

    // pAnimal = pBird;
    // pAnimal->say();


    // Задание 3: Что если теперь сделать метод say базового класса виртуальным
    // Что программа напечатает в первых двух заданиях


    // Задание 4: В следующем участке кода p->say() вызывает один и тот же метод или разные?
    // Проверьте это в слачае если метод say базового класса виртуальный и невиртуальный
    // Animal* p = &animal;
    // p->say();
    // p = &bird;
    // p->say();


    // Задание 5: Проверьте, будет ди работать такой же механизм для ссылок

}