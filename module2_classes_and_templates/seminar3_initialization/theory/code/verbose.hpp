#pragma once

namespace {

class Verbose
{
private:
    std::string name {};

public:
    Verbose()   
    {
        std::cout << "Default Constructor (" << name << ")" << std::endl;
    }

    ~Verbose()  
    {
        std::cout << "Destructor (" << name << ")" << std::endl;
    }

    Verbose(const std::string& name) : name(name)
    {
        std::cout << "Constructor from std::string (" << name << ")" << std::endl;
    }

    Verbose(const Verbose& v) : name(v.name) 
    {
        std::cout << "Copy Constructor (" << name << ")" << std::endl;
    }

    Verbose& operator=(const Verbose& v)
    {
        name = v.name;
        std::cout << "Copy Assignment Operator (" << name << ")" << std::endl;
        return *this;
    }

    std::string getName() const 
    {
        return name;
    }
};

}