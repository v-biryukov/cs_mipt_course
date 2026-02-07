#include <iostream>
#include <cassert>
#include <string>
#include <iomanip>

using namespace std::string_literals;


#define private public
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//          Тут нужно реализовать класс большого числа
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||


#include "n.hpp"


// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
/**/

bool operator==(const Number& object, const Number& other) 
{
    if (object.size != other.size)
        return false;

    for (std::size_t i = 0; i < object.size; ++i) 
    {
        if (object.data[i] != other.data[i])
            return false;
    }
    return true;
}

bool operator!=(const Number& object, const Number& other) 
{
    return ! (object == other);
}


/**/
// |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
using NumType = Number;


void testConstructorDefault()
{
    NumType n {};
    assert(n.data != nullptr);
    assert(n.size == 1);
    assert(n.data[n.size - 1] == 0);
}


void testConstructorInt()
{
    NumType n1(0);
    assert(n1.data != nullptr);
    assert(n1.size == 1);
    assert(n1.data[n1.size - 1] == 0);

    NumType n2(12345678);
    assert(n2.data != nullptr);
    assert(n2.size == 4);
    assert(n2.data[n1.size - 1] == 78);

    NumType n3(1234567);
    assert(n3.data != nullptr);
    assert(n3.size == 4);
    assert(n3.data[n1.size - 1] == 67);
}

void testConstructorString() 
{
    NumType n0("0");
    assert(n0.data != nullptr);
    assert(n0.size == 1);
    assert(n0.data[n0.size - 1] == 0);

    NumType n1("1");
    assert(n1.data != nullptr);
    assert(n1.size == 1);
    assert(n1.data[n1.size - 1] == 1);

    NumType n2("12345678");
    assert(n2.data != nullptr);
    assert(n2.size == 4);
    assert(n2.data[n1.size - 1] == 78);

    NumType n3("1234567");
    assert(n3.data != nullptr);
    assert(n3.size == 4);
    assert(n3.data[n1.size - 1] == 67);

    NumType n4("123456789987654321123456789987654321123456789987654321123456789987654321");
    assert(n4.data != nullptr);
    assert(n4.data[n1.size - 1] == 21);

    NumType n2s("12345678"s);
    assert(n2s == n2);
}

void testCopyAndAssign() 
{
    NumType n1(4567);
    NumType n2 = n1;
    NumType n3;
    n3 = n1;

    assert(n1 == n2);
    assert(n1 == n3);
}

void testAddition() 
{
    NumType a(1234);
    NumType b(5678);
    NumType c1 = a + b;
    NumType c2(6912);
    assert(c1 == c2);

    a += b;
    assert(a == c1);
    assert(a == c2);

    assert(b + b == NumType(11356));
    assert(b + NumType{0} == b);
    assert(NumType{0} + b == b);

    assert(NumType{9} + NumType{1} == NumType{10});
    assert(NumType{99} + NumType{1} == NumType{100});
    assert(NumType{99999999} + NumType{1} == NumType{100000000});
}

/**/
void testMultiplication() 
{
    NumType a(1234);
    NumType b(5678);
    NumType c1 = a * b;
    NumType c2(7006652);

    assert(c1 == c2);

    NumType d(0);
    assert(a * d == NumType{0});
    assert(d * a == NumType{0});

    NumType e(1);
    assert(a * e == a);
    assert(e * a == a);
}
/**/

void testIsEven() 
{
    NumType a(100);
    NumType b(101);
    assert(a.isEven());
    assert(!b.isEven());
}

int main()
{
    testConstructorDefault();
    testConstructorInt();
    testConstructorString();
    testCopyAndAssign(); 
    testAddition(); 
    testMultiplication(); 
    testIsEven();
}