/*
    Класс Number - класс положительных больших чисел

    Большое число будет храниться в массиве в сегменте куча.
    В самом объекте будем хранить указатель на данные в куче.
    Также, в самом объекте будут храниться размер и вместимость массива.

        data - указатель, на элементы, хранящиеся в куче.
        capacity - размер массива data.
        size - сколько ячеек занимет число в массиве data, size <= capacity.

    По условию задачи класс Number должен поддерживать только положительные числа.
    Это сделано для того, чтобы задача не была слишком сложной.

    Каждый элемент массива должен содержать разряд числа в 100-ричной системе счисления (так как base = 100).
    По сути, каждый элемент массива должен хранить две цифры числа в десятичной записи.

    Значение 100 для системы счисления выбрано для того, чтобы задача была не такой сложной.
    Если выбрать значения базы 256 (максимально эффективное использование памяти для типа, размером 1 байт),
    то алгоритм печати на экран усложнится. Наиболее эффективный вариант - использование 64 битных чисел
    (то есть uint64_t вместо char) и базы 2^64, но это бы ещё сильнее усложнило эту задачу.

    Для удобства разряды числа хранятся в обратном порядке (это упрощает многие алгоритмы с такими числами). 
    Например, число 12345678 соответствует массиву:
    
        {78, 56, 34, 12}
    
    Для выделения/освобождения памяти в куче были использованы операторы new[] и delete[].
    Хотя можно было бы и использовать функции malloc и free из библиотеки cstdlib.

    Выделение/освобождения с использованием malloc/free:

        data = static_cast<char*>(std::malloc(capacity * sizeof(char)));
        ...
        std::free(data);

    То же самое с использованием new[]/delete[]:

        data = new char[capacity];
        ...
        delete[] data;

*/
#pragma once

#include <iostream>
#include <iomanip>

class Number 
{
private:
    static const int base = 100;

    char* data;
    std::size_t size;
    std::size_t capacity;

public:

    Number(int a) 
    {
        // Находим размер необходимой памяти под это число
        int temp = a;
        capacity = 0;
        while (temp != 0) 
        {
            temp /= base;
            capacity += 1;
        }

        // Отдельно обрабатываем случай, когда число равно 0
        if (capacity == 0) 
            capacity = 1;

        // Выделяем память в куче и записывем число a в массив data
        data = new char[capacity];

        for (int i = 0; i < capacity; ++i) 
        {
            data[i] = a % base;
            a /= base;
        }

        // В данном случае размер будет равен вместимости
        size = capacity;
    }

    bool operator==(const Number& other) const 
    {
        if (size != other.size)
            return false;

        for (std::size_t i = 0; i < size; ++i) 
        {
            if (data[i] != other.data[i])
                return false;
        }
        return true;
    }

    bool operator!=(const Number& other) const 
    {
        return ! (*this == other);
    }


    ~Number() 
    {
        // Освобождаем память в куче
        delete [] data;
    }


    friend std::ostream& operator<<(std::ostream& stream, const Number& num);
};

std::ostream& operator<<(std::ostream& stream, const Number& num)
{
    // Печатаем самый большой разряд
    stream << static_cast<int>(num.data[num.size - 1]);

    // Печатаем остальные разряды с заполнением нулями до 2-х цифр
    // setfill и setw используются для того, чтобы замостить ноликом, элемент будет меньше чем 10.
    for (std::size_t i = 0; i < num.size - 1; ++i)
        stream << std::setfill('0') << std::setw(2) << static_cast<int>(num.data[num.size - 2 - i]);

    return stream;
}

