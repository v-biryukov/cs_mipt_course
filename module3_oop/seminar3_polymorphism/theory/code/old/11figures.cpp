#include <iostream>
#include <string>
#include <cmath>

using std::cout;
using std::endl;

struct Vector2f
{
    float x, y;
};

Vector2f operator+(Vector2f left, Vector2f right)
{
    Vector2f result = {left.x + right.x, left.y + right.y};
    return result;
}
Vector2f operator*(Vector2f left, float right)
{
    Vector2f result = {left.x * right, left.y * right};
    return result;
}
Vector2f operator*(float left, Vector2f right)
{
    Vector2f result = {left * right.x, left * right.y};
    return result;
}

Vector2f& operator+=(Vector2f& left, Vector2f right)
{
    left.x += right.x;
    left.y += right.y;
    return left;
}

float distance(Vector2f a, Vector2f b)
{
    return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


class Triangle
{
private:
    Vector2f mPointA;
    Vector2f mPointB;
    Vector2f mPointC;

public:
    Triangle(Vector2f pointA, Vector2f pointB, Vector2f pointC) : 
             mPointA(pointA), mPointB(pointB), mPointC(pointC) {}

    float getPerimeter()
    {
        return distance(mPointA, mPointB) + distance(mPointB, mPointC) + distance(mPointC, mPointA);
    }

    float getArea()
    {
        float a = distance(mPointA, mPointB);
        float b = distance(mPointB, mPointC);
        float c = distance(mPointC, mPointA);

        float p = (a + b + c) / 2;
        return std::sqrt(p * (p - a) * (p - b) * (p - c));
    }
};

int main()
{
    Triangle t {{0, 1}, {2, 2}, {1, 0}};
    cout << t.getArea() << endl;

    /* 
	В данной задаче рассматриваем иерархию наследования фигур
	без привязки к системе координат

    Задание:
	1) 	Создайте интерфейс IFigure от которого будет наследоваться Triangle
		Этот интерфейс должен содержать 2 абстрактных метода :
		getPerimeter и getArea

	2) 	Создайте классы Rectangle (прямоугольник) и Circle (круг)
		которые будут наследоваться от класса IFigure

	3) 	Создайте вектор из указателей на случайные объекты 
		Статический тип у элементов должен быть IFigure*
		А динамический тип -- указатель на объект одного их трёх наследуемых типов

	4) 	Напечатайте через пробел периметер каждой фигуры из этого вектора

	5) 	Напишите функцию, которая будет принимать на вход такой вектор (по константной ссылке)
		и возвращать суммарную площадь всех фигур
}