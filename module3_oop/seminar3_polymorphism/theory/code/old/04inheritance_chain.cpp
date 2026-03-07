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
class Colibri : public Bird {
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



int main()
{
    Animal animal("Abstract", 100);
    Bird bird("Bubba", 2, 800);
    Colibri colibri("Coco", 1, 100);

    Animal* pAnimal = &animal;
    Bird* pBird = &bird;
    Colibri* pColibri = &colibri;

    // В данном участке кода ключевое слово virtual написано только у метода базового класса
    
    // Задание 1: Присваиваем указателю на объект базового класса 
    //            указатель на объект класса ребёнка ребёнка
    // Какой метод say вызовется:
    // Из класса Colibri, из класса Bird или из класса Animal?

    // pAnimal = pColibri;
    // pAnimal->say();


    // Задание 2: Если убрать ключевое слово virtual из метода базового класса,
    //            то какой метод вызовется в первом задании?


    // Задание 3: Что напечатают следующие 2 строки кода?
    //            Проверьте для случаев когда:
    //            1: ни одна из функций не помечена как virtual
    //            2: только метод say базового класса помечен как virtual
    //            3: только метод say класса Bird помечен как virtual

    // pBird = pColibri;
    // pBird->say();


    // Задание 4: В следующем участке кода p->say() вызывает один и тот же метод или разные?
    // Проверьте это в слачае если метод say базового класса виртуальный и невиртуальный
    // Animal* p = &animal;
    // p->say();
    // p = &bird;
    // p->say();
    // p = &colibri;
    // p->say();

}