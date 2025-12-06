#include <iostream>
#include <cassert>
#include <string>
#include <optional>
using namespace std::string_literals;


// /////////////////////////////////////////////////////////////////
// Тут вам нужно написать вашу реализацию шаблонного класса Optional

// /////////////////////////////////////////////////////////////////


template<typename T>
using OptType = Optional<T>;
using OptExceptionType = BadOptionalAccess;
/**/

/*
template<typename T>
using OptType = std::optional<T>;
using OptExceptionType = std::bad_optional_access;
/**/


void testDefaultConstructor() 
{
    OptType<int> o;
    assert(!o.has_value());
    assert(!static_cast<bool>(o));
}

void testValueConstructor() 
{
    OptType<int> o(100);
    assert(o.has_value());
    assert(*o == 100);
    assert(o.value() == 100);
}

void testCopyConstructor() 
{
    OptType<int> o1(100);
    OptType<int> o2 = o1;

    assert(o2.has_value());
    assert(o2.value() == 100);
}

void testCopyConstructorEmpty() 
{
    OptType<int> o1;
    OptType<int> o2(o1);
    assert(!o2.has_value());
}

void testTemplateCopyConstructor() 
{
    OptType<int> oi(100);
    OptType<double> od(oi);

    assert(od.has_value());
    assert(*od == 100.0);
}

void testAssignment() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    o2 = o1;
    assert(o2.has_value());
    assert(*o2 == 100);
}

void testTemplateAssignment() 
{
    OptType<int> oi(100);
    OptType<double> od;

    od = oi;
    assert(od.has_value());
    assert(*od == 100.0);
}

void testSelfAssignment() 
{
    OptType<int> o(100);
    o = o; 
    assert(o.has_value());
    assert(o.value() == 100);
}


void testValueConstructorString() 
{
    OptType<std::string> o("Axolotl");
    assert(o.has_value());
    assert(*o == "Axolotl");
    assert(o.value() == "Axolotl");
}

void testCopyConstructorString() 
{
    OptType<std::string> o1("Axolotl");
    OptType<std::string> o2 = o1;

    assert(o2.has_value());
    assert(o2.value() == "Axolotl");
}

void testCopyConstructorEmptyString() 
{
    OptType<std::string> o1;
    OptType<std::string> o2(o1);
    assert(!o2.has_value());
}

void testAssignmentString() 
{
    OptType<std::string> o1("Axolotl");
    OptType<std::string> o2;

    o2 = o1;
    assert(o2.has_value());
    assert(*o2 == "Axolotl");
}


void testReset() 
{
    OptType<int> o(100);
    assert(o.has_value());

    o.reset();
    assert(!o.has_value());
}

void testValueOr() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    assert(o1.value_or(200) == 100);
    assert(o2.value_or(200) == 200);
}

void testBoolCast() 
{
    OptType<int> o1(100);
    OptType<int> o2;

    if (!o1)
    {
        assert(false);
    }

    if (o2)
    {
        assert(false);
    }
}

void testThrowOnValue() 
{
    OptType<int> o;

    try 
    {
        o.value();
        assert(false);
    } 
    catch (const OptExceptionType&) {} 
    catch (...) {assert(false);}
}

void testConstOptTypeAccess() 
{
    const OptType<int> o1(100);
    assert(o1.has_value());
    assert(*o1 == 100);
    assert(o1.value() == 100);
    assert(o1.value_or(200) == 100);

    const OptType<int> o2;
    assert(!o2.has_value());
    assert(o2.value_or(200) == 200);

    try 
    {
        o2.value();
        assert(false);
    } 
    catch (const OptExceptionType&) {}
    catch (...) {assert(false);}
}


void testAlignment() 
{
    assert(alignof(int) == alignof(OptType<int>));
    assert(alignof(std::string) == alignof(OptType<std::string>));
}

struct NoDefault 
{
    int x;
    NoDefault(int v) : x(v) {}
    NoDefault() = delete;
};

void testNoDefaultConstructor() 
{
    OptType<NoDefault> o(NoDefault(100));
    assert(o.has_value());
    assert(o.value().x == 100);
}


struct Object 
{
    static int count;
    Object()
    {
        count += 1;
    }

    Object(const Object& other)
    {
        count += 1;
    }

    ~Object()
    {
        count -= 1;
    }
};

int Object::count {0};


void testCreationDestruction1() 
{
    Object::count = 0;

    OptType<Object> o;
    assert(Object::count == 0);
}

void testCreationDestruction2()
{
    Object::count = 0;

    OptType<Object> o(Object{});
    assert(Object::count == 1);

    o.reset();
    assert(Object::count == 0);
}

void testCreationDestruction3()
{
    Object::count = 0;

    OptType<Object> o(Object{});
    o = OptType<Object>{};
    assert(Object::count == 0);
}

void testCreationDestruction4()
{
    OptType<Object> o1(Object{});
    OptType<Object> o2 = o1;

    assert(Object::count == 2);
}

void testCreationDestruction5()
{
    OptType<Object> o(Object{});
    int before = Object::count;
    o = o;
    assert(Object::count == before);
}


int main()
{
    try
    {
        testDefaultConstructor();
        testValueConstructor();
        testCopyConstructor();
        testCopyConstructorEmpty();
        testTemplateCopyConstructor();
        testAssignment();
        testTemplateAssignment();
        testSelfAssignment();

        testValueConstructorString();
        testCopyConstructorString();
        testCopyConstructorEmptyString();
        testAssignmentString();

        testReset();
        testValueOr();
        testBoolCast();
        testThrowOnValue();
        testConstOptTypeAccess();
        testAlignment();
        testNoDefaultConstructor();
        testCreationDestruction1();
        testCreationDestruction2();
        testCreationDestruction3();
        testCreationDestruction4();
        testCreationDestruction5();
    }
    catch (...)
    {
        std::cerr << "Exception was thrown" << std::endl;
        std::exit(1);
    }

    std::cout << "Success. All tests are passed!" << std::endl;
}