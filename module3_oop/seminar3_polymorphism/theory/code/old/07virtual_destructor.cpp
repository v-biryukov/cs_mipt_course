#include <iostream>
#include <string>

using std::cout;
using std::endl;

class Animal {
protected:
    std::string mName;
    int mAge;
public:
    Animal(std::string name, int age) : mName(name), mAge(age)
    {
        cout << "Animal Constructor" << endl;
    }

    virtual void say() const
    {
        cout << "<abstract sounds>" << endl;
        cout << "My name is " << mName <<". I am " << mAge << " old. " << endl << endl; 
    }

    void increaseAge()
    {
        mAge++;
    }

    ~Animal() 
    {
        cout << "Animal Destructor" << endl;
    }
};


// Класс Bird наследуется от Animal
class Bird : public Animal {
protected:
    int mNumFeathers;
public:
    // Конструктор Bird вызывает конструктор Animal
    Bird(std::string name, int age, int numFeathers) 
        : Animal(name, age), mNumFeathers(numFeathers)
    {
        cout << "Bird Constructor" << endl;
    }

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

    ~Bird() 
    {
        cout << "Bird Destructor" << endl;
    }
};

/* Класс TrackableBird
    Класс птицы, которая отслеживается с помощью датчиков
    Мы храним массив высот в куче
    Конечно, тут лучше было бы использовать std::vector для хранения высот.
    Но, данный пример нужен для того чтобы показать зачем нужен виртуальный деструктор.
*/
class TrackableBird : public Bird {
protected:
    const size_t mHeightCapacity = 100;
    size_t mHeightSize;
    float* mHeights;
public:
    // Конструктор TrackableBird вызывает конструктор Bird
    TrackableBird(std::string name, int age, int numFeathers) 
        : Bird(name, age, numFeathers)
    {
        cout << "TrackableBird Constructor (alocating memory)" << endl;
        mHeights = new float[mHeightCapacity];
    }

    void addHeight(float h)
    {
        mHeights[mHeightSize] = h;
        mHeightSize++;
    }

    ~TrackableBird() 
    {
        cout << "TrackableBird Destructor (freeing memory)" << endl;
        delete [] mHeights;
    }
};


int main()
{

    // Задание 1: В каком порядке вызовутся конструкторы и деструкторы в следующей строке?
    // TrackableBird t {"Tweety", 10, 200};


    // Задание 2: В каком порядке вызовутся конструкторы и деструкторы в следующем коде?
    // TrackableBird* pt = new TrackableBird {"Tweety", 10, 200};
    // delete pt;


    // Задание 3: В каком порядке вызовутся конструкторы и деструкторы в следующем коде?
    // Animal* pa = new TrackableBird {"Tweety", 10, 200};
    // delete pa;


    // Задание 4: В каком порядке вызовутся конструкторы и деструкторы в следующем коде?
    // Bird* pb = new TrackableBird {"Tweety", 10, 200};
    // delete pb;


    // Задание 5: Исправьте код так, чтобы освобождение памяти всегда происходило
    //            Подсказка: Добавьте виртуальный деструктор
}