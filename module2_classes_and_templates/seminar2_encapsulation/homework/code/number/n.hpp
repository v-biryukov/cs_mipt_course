#pragma once

#include <iostream>
#include <iomanip>
#include <string>

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

        for (size_t i = 0; i < capacity; ++i)
        {
            data[i] = a % base;
            a /= base;
        }

        // В данном случае размер будет равен вместимости
        size = capacity;
    }

    ~Number() 
    {
        // Освобождаем память в куче
        delete [] data;
    }

    friend std::ostream& operator<<(std::ostream& stream, const Number& num);

    Number() 
    {
        capacity = 1;
        data = new char[capacity];
        data[0] = 0;
        size = 1;
    }

    Number(const Number& n) 
    {
        capacity = n.capacity;
        size = n.size;
        data = new char[capacity];

        for (std::size_t i = 0; i < size; ++i) 
        {
            data[i] = n.data[i];
        }
    }

    Number(const std::string& str) 
    {
        if (str.empty()) 
        {
            capacity = 1;
            data = new char[capacity];
            data[0] = 0;
            size = 1;
            return;
        }

        std::size_t str_size = str.size();
        capacity = (str_size + 1) / 2;
        data = new char[capacity];
        size = capacity;

        for (std::size_t i = 0; i < capacity; ++i) 
        {
            int val = 0;
            int pwr = 1;
            
            for (int j = 0; j < 2; ++j) 
            {
                std::size_t pos = str_size - 1 - i * 2 - j;
                if (pos < str_size) 
                {
                    val = val + (str[pos] - '0') * pwr;
                    pwr = pwr * 10;
                }
            }
            data[i] = val;
        }
    }

    Number& operator=(const Number& n) 
    {
        if (this == &n) 
        {
            return *this;
        }
        
        delete[] data;
        
        capacity = n.capacity;
        size = n.size;
        data = new char[capacity];
        for (std::size_t i = 0; i < size; ++i) 
        {
            data[i] = n.data[i];
        }
        
        return *this;
    }

    Number operator+(const Number& other) const 
    {
        Number res;
        std::size_t max_size;

        if (size > other.size) 
        {
            max_size = size;
        }
        else 
        {
            max_size = other.size;
        }
        
        res.size = max_size + 1;
        res.capacity = res.size;
        delete[] res.data;
        res.data = new char[res.capacity];
        
        int ind = 0;
        for (std::size_t i = 0; i < res.size; ++i) 
        {
            int sum = ind;
            
            if (i < size) 
            {
                sum = sum + data[i];
            }
            
            if (i < other.size) 
            {
                sum = sum + other.data[i];
            }
            
            res.data[i] = sum % base;
            ind = sum / base;
        }
        
        if (res.data[res.size - 1] == 0) 
        {
            res.size = res.size - 1;
        }
        
        return res;
    }

    Number& operator+=(const Number& other) 
    {
        *this = *this + other;
        return *this;
    }

    bool isEven() const 
    {
        if ((data[0] % 2) == 0) 
        {
            return true;
        }

        else 
        {
            return false;
        }
    }

    Number operator*(const Number& other) const 
    {
        Number res;
        res.size = size + other.size;
        res.capacity = res.size;
        delete[] res.data;
        res.data = new char[res.capacity];
        
        for (std::size_t i = 0; i < res.size; ++i) 
        {
            res.data[i] = 0;
        }
        
        for (std::size_t i = 0; i < size; ++i) 
        {
            int ind = 0;
            for (std::size_t j = 0; j < other.size; ++j) 
            {
                int product = data[i] * other.data[j] + res.data[i + j] + ind;
                res.data[i + j] = product % base;
                ind = product / base;
            }
            if (ind > 0) 
            {
                res.data[i + other.size] = res.data[i + other.size] + ind;
            }
        }
        
        while (res.size > 1 && res.data[res.size - 1] == 0) 
        {
            res.size = res.size - 1;
        }
        
        return res;
    }

    Number& operator*=(const Number& other) 
    {
        *this = *this * other;
        return *this;
    }
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

Number fibonacci(int n) 
{
    if (n == 0) 
    {
        return Number("0");
    }
    
    if (n == 1) 
    {
        return Number("1");
    }
    
    Number a("0");
    Number b("1");
    Number c;
    
    for (int i = 2; i <= n; ++i) 
    {
        c = a + b;
        a = b;
        b = c;
    }
    
    return b;
}

Number factorial(int n) 
{
    Number res("1");
    
    for (int i = 2; i <= n; ++i) 
    {
        Number item(std::to_string(i));
        res = res * item;
    }
    return res;
}