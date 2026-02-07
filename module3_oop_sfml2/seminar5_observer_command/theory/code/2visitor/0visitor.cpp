#include <iostream>
#include <string>

class Circle;
class Square;

class Visitor 
{
public:
    virtual void visit(Circle& circle) = 0;
    virtual void visit(Square& square) = 0;
    virtual ~Visitor() = default;
};


class Shape 
{
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Shape() = default;
};


class Circle : public Shape 
{
private:
    double radius;

public:
    Circle(double r) : radius(r) {}

    double getRadius() const 
    {
        return radius;
    }

    void accept(Visitor& visitor) override 
    {
        visitor.visit(*this);
    }
};


class Square : public Shape 
{
private:
    double side;

public:
    Square(double s) : side(s) {}

    double getSide() const 
    {
        return side;
    }

    void accept(Visitor& visitor) override
    {
        visitor.visit(*this);
    }
};


class AreaVisitor : public Visitor 
{
public:
    void visit(Circle& circle) override 
    {
        double area = 3.14159 * circle.getRadius() * circle.getRadius();
        std::cout << "Area of Circle: " << area << std::endl;
    }

    void visit(Square& square) override
     {
        double area = square.getSide() * square.getSide();
        std::cout << "Area of Square: " << area << std::endl;
    }
};

class XMLExportVisitor : public Visitor 
{
public:
    void visit(Circle& circle) override 
    {
        std::cout << "<Circle radius=\"" << circle.getRadius() << "\"/>" << std::endl;
    }

    void visit(Square& square) override 
    {
        std::cout << "<Square side=\"" << square.getSide() << "\"/>" << std::endl;
    }
};

int main() 
{
    Circle circle(5.0);
    Square square(4.0);

    AreaVisitor areaVisitor;
    XMLExportVisitor xmlVisitor;

    std::cout << "Calculating areas:" << std::endl;
    circle.accept(areaVisitor);
    square.accept(areaVisitor);

    std::cout << "\nExporting to XML:" << std::endl;
    circle.accept(xmlVisitor);
    square.accept(xmlVisitor);

    return 0;
}