/*
    Заменим копирование с помощью цикла на memcpy.
    
    Как правило функция memcpy работает значительно быстрее, чем цикл.
    Правда, часто компилятор сам заменяет цикл на memcpy при оптимизации.
*/

#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <cstring>

class String 
{
private:

    std::size_t mSize        {0};
    std::size_t mCapacity    {0};
    char* mpData             {nullptr};

public:

    String(const char* str) 
    {
        std::size_t strSize = std::strlen(str);
        resize(strSize);
        std::memcpy(mpData, str, mSize);
    }

    String() : String("") {}
    String(const String& s) : String(s.cStr()) {}

    String(std::size_t n, char a)
    {
        resize(n);

        for (std::size_t i = 0; i < mSize; ++i)
            mpData[i] = a;
    }

    ~String()
    {
        delete[] mpData;
    }

    void reserve(std::size_t capacity)
    {
        if (capacity <= mCapacity)
            return;

        mCapacity = std::max(2 * mCapacity, capacity);
        char* newData = new char[mCapacity];

        if (mpData)
            std::memcpy(newData, mpData, mSize + 1);

        delete[] mpData;
        mpData = newData;
    }


    void resize(std::size_t size)
    {
        reserve(size + 1);
        mSize = size;
        mpData[mSize] = '\0';
    }


    String& operator=(const String& right)
    {
        if (this == &right)
            return *this;

        mSize = right.mSize;
        resize(mSize);

        std::memcpy(mpData, right.mpData, mSize + 1);

        return *this;
    }


    String operator+(const String& b)
    {
        String result;
        result.resize(mSize + b.mSize);

        std::memcpy(result.mpData, mpData, mSize);
        std::memcpy(result.mpData + mSize, b.mpData, b.mSize);
        result.mpData[result.mSize] = '\0';

        return result;
    }

    String& operator+=(const String& right)
    {
        *this = *this + right;
        return *this;
    }

    bool operator==(const String& right) const
    {
        if (mSize != right.mSize)
            return false;

        std::size_t i = 0;
        while (i < mSize && mpData[i] == right.mpData[i])
            i++;

        return i == mSize;
    }

    bool operator<(const String& right) const
    {
        std::size_t i = 0;
        while (i < mSize && i < right.mSize && mpData[i] == right.mpData[i])
            i++;

        return mpData[i] < right.mpData[i];
    }

    bool operator>(const String& right) const
    {
        return right < *this;
    }

    bool operator>=(const String& right) const
    {
        return !(*this < right);
    }

    bool operator<=(const String& right) const
    {
        return !(right < *this);
    }

    bool operator!=(const String& right) const
    {
        return !(*this == right);
    }

    char& operator[](std::size_t i)
    {
        return mpData[i];
    }

    char& at(std::size_t i)
    {
        if (i >= mSize)
        {
            throw std::out_of_range{}
        }
        return mpData[i];
    }

    void clear()
    {
        delete[] mpData;

        mSize = 0;
        mCapacity = 1;
        mpData = new char[mCapacity];
        mpData[0] = '\0';
    }

    void addCharacter(char c)
    {
        if (mSize + 1 == mCapacity)
            reserve(2 * mCapacity);

        mpData[mSize] = c;
        resize(mSize + 1);
    }


    std::size_t getSize()        const   {return mSize;}
    std::size_t getCapacity()    const   {return mCapacity;}
    const char* cStr()      const   {return mpData;}
};


std::ostream& operator<<(std::ostream& out, const String& s) 
{
    out << s.cStr();
    return out;
}

std::istream& operator>>(std::istream& in, String& s) 
{
    s.clear();
    while (true)
    {
        char x = in.get();
        if (x == ' ' || x == '\n' || x == '\t')
            break;
        s.addCharacter(x);
    }
    return in;
}


int main() 
{
    String t1 = "";
    std::cout << t1 << " " << t1.getSize() << " " << t1.getCapacity() << std::endl;

    for (int i = 0; i < 100; ++i)
    {
        t1 += "a";
        std::cout << t1 << " " << t1.getSize() << " " << t1.getCapacity() << std::endl;
    }

    std::cout << t1 << " " << t1.getSize() << " " << t1.getCapacity() << std::endl;


    String a = "Mouse";

    std::cout << "Hello2" << std::endl;
    String b;
    std::cin >> b;
    String c = b;

    if (a + c == "MouseLion")
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;


    if (a > "Mice")
        std::cout << "Yes" << std::endl;
    else
        std::cout << "No" << std::endl;


    c.at(0) = 'P';
    std::cout << c << std::endl;

    c += a;
    std::cout << c << std::endl;

    c = c + String(10, 'q');
    std::cout << c << std::endl;
}