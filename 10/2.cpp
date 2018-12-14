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

	Rectangle(string in_type, double in_w, double in_h)		// �簢�� ������ ����
		: Shape(in_type,in_w,in_h)
	{}
	double getArea()			// getArea() �������̵�
	{
		return width * height;
	}
};

class Triangle : public Shape
{
public:
	// �θ� ������ �״�� Ȱ��
	Triangle(string in_type, double in_w, double in_h)		// �ﰢ�� ������ ����
	: Shape(in_type, in_w, in_h)
	{}
	 double getArea() 			// getArea() �������̵�
	{
		return width * height * 0.5;
	}
};

class Oval : public Shape
{
public:
	// �θ� ������ �״�� Ȱ��
	Oval(string in_type, double in_w, double in_h)			// Ÿ�� ������ ����
	: Shape(in_type, in_w, in_h)
	{}
	double getArea()			// getArea() �������̵�
	{
		return width * height * 3.141592;
	}
};



int main()
{
	Rectangle rectangle("Rectangle", 1.5, 2.0);
	Triangle triangle("Triangle", 1.5, 2.0);
	Oval oval("Oval", 1.5, 2.0);

	cout << rectangle.getType() << " �� ���̴� : " << rectangle.getArea() << endl;
	cout << triangle.getType() << " �� ���̴� : " << triangle.getArea() << endl;
	cout << oval.getType() << " �� ���̴� : " << oval.getArea() << endl;

	return 0;
}