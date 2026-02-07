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

    virtual void say(const std::string& phrase) const
    {
        cout << "<abstract sounds> " << phrase << endl;
    }

    virtual ~Animal() {};
};

class Cat : public Animal {
private:
    int mNumMiceCaught;
public:
    // Конструктор Cat вызывает конструктор Animal
    Cat(std::string name, int age, int numMiceCaught) 
        : Animal(name, age), mNumMiceCaught(numMiceCaught) {}

    void say(const std::string& phrase) const override
    {
        cout << "Meow! " << phrase << endl; 
    }
};



int main()
{
    /*
        В данном примере метод say базового класса принимает на вход строку по константной ссылке
        А метод say класса Cat принимает на вход указатель char*
        Типы аргументов не совпадают!
    */
    
    // Задание 1:
    // Какой метод say вызовется в этом случае при исполнении следующего кода:
    Animal* p = new Cat {"Cleo", 10, 100};
    p->say("Hello");
    delete p;


    // Задание 2:
    // Какой метод say вызовется для следующих вариантов метода say класса Cat:
    //      - void say(const char* phrase) const
    //      - void say(std::string phrase) const
    //      - void say(const std::string& phrase) const
    //      - void say(const std::string& phrase)


    /* Задание 3: Что произойдёт, если заменить метод say класса Cat на такой:
        int say(std::string phrase) const
        {
            cout << "Meow! " << phrase << endl;
            return 1;
        }
    */


    /* Задание 4: 
    Проблемма в примерах выше заключается в том, что компилятор не выдаёт ошибку 
    в том случае когда сигнатура методов не совпадает
    Так как компилятор не может понять действительно ли вы хотели переопределить
    метод say или вы хотели перегрузить его с другими параметрами

    Используйте ключевое слово override, и сделайте так чтобы компилятор выдавал
    ошибку при несовпадении сигнатур методов:

        void say(char* phrase) const override
    
    Так компилятор будет знать, что метод say должен обязательно переопределять
    метод базового класса, а не перегружать его.
    */

}