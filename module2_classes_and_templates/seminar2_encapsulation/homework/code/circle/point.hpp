#pragma once
#include <iostream>
#include <cmath>

class Point
{
private:
    float x;
    float y;

public:  
    Point()
    {
        x = 0;
        y = 0;
    }

    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    
    float getX() const {return x;}
    float getY() const {return y;}
    void setX(float x) {this->x = x;}
    void setY(float y) {this->y = y;}

    float distance(Point p) const
    {
        return std::sqrt((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y));
    }

    float norm() const
    {
        return std::sqrt(x * x + y * y);
    }

    Point operator+(Point right) const
    {
        Point result = {x + right.x, y + right.y};
        return result;
    }
};


std::ostream& operator<<(std::ostream& left, Point right) 
{
    left << "(" << right.getX() << ", " << right.getY() << ")";
    return left;
}