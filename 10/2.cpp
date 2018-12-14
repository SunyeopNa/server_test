#include <iostream>
#include <String>

using namespace std;

class Shape {
protected :
	
	string type;
	double width, height;

public :
	Shape(string in_type, double in_w, double in_h)
		:type(in_type), width(in_w), height(in_h)
	{}

	virtual double getArea() { return 0; }
	string getType() { return type; }
};

class Rectangle : public Shape
{
public:

	Rectangle(string in_type, double in_w, double in_h)		// 사각형 생성자 구현
		: Shape(in_type,in_w,in_h)
	{}
	double getArea()			// getArea() 오버라이딩
	{
		return width * height;
	}
};

class Triangle : public Shape
{
public:
	// 부모 생성자 그대로 활용
	Triangle(string in_type, double in_w, double in_h)		// 삼각형 생성자 구현
	: Shape(in_type, in_w, in_h)
	{}
	 double getArea() 			// getArea() 오버라이딩
	{
		return width * height * 0.5;
	}
};

class Oval : public Shape
{
public:
	// 부모 생성자 그대로 활용
	Oval(string in_type, double in_w, double in_h)			// 타원 생성자 구현
	: Shape(in_type, in_w, in_h)
	{}
	double getArea()			// getArea() 오버라이딩
	{
		return width * height * 3.141592;
	}
};



int main()
{
	Rectangle rectangle("Rectangle", 1.5, 2.0);
	Triangle triangle("Triangle", 1.5, 2.0);
	Oval oval("Oval", 1.5, 2.0);

	cout << rectangle.getType() << " 의 넓이는 : " << rectangle.getArea() << endl;
	cout << triangle.getType() << " 의 넓이는 : " << triangle.getArea() << endl;
	cout << oval.getType() << " 의 넓이는 : " << oval.getArea() << endl;

	return 0;
}