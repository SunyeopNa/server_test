#include <iostream>
#include <string>
using namespace std;

class Circle
{
	int radius;
public:
	Circle() {};
	Circle(int radius) :radius(radius) {	}

	int getRadius()
	{
		return radius;
	}
	friend ostream& operator << (ostream& os, Circle& circle)
	{
		cout << "radius : " << circle.getRadius();
		return os;
	}
};

template <class T>
class MyVector
{
private:
	int size;
	int maxSize;
	T* list;
public:
	MyVector()
	{
		size = 0;
		maxSize = 3;
		list = new T[maxSize];
	}
	~MyVector()
	{
		delete[] list;
	}
	MyVector& pushBack(T element)
	{
		if (size < maxSize)
		{
			list[size++] = element;
		}
		else
		{
			cout << "MyVector 확장!" << endl;

			T* newList = new T[maxSize + 10];
			for (int i = 0; i < maxSize; i++)
				newList[i] = list[i];

			newList[size++] = element;
			maxSize += 10;

			delete[] list;
			list = newList;
		}
		cout << "push : " << element << endl;
		return *this;
	}

	void print()
	{
		for (int i = 0; i < size; i++)
			cout << list[i];
		cout << endl << endl;
	}
};

template <>
class MyVector<Circle>
{
private:
	int size;
	int maxSize;
	Circle* list;
public:
	MyVector()
	{
		size = 0;
		maxSize = 3;
		list = new Circle[maxSize];
	}
	~MyVector()
	{
		delete[] list;
	}
	MyVector& pushBack(Circle element)
	{
		if (size < maxSize)
		{
			list[size++] = element;
		}
		else
		{
			cout << "MyVector 확장!" << endl;

			Circle* newList = new Circle[maxSize + 10];
			for (int i = 0; i < maxSize; i++)
				newList[i] = list[i];

			newList[size++] = element;
			maxSize += 10;

			delete[] list;
			list = newList;
		}
		cout << element << endl;
		return *this;
	}

	void print()
	{
		int result = 0;
		for (int i = 0; i < size; i++)
			result += list[i].getRadius();
		cout << "Sum of radius : " << result << endl << endl;
	}
};

int main()
{
	MyVector<int> intV;
	intV.pushBack(1).pushBack(2).pushBack(3).pushBack(4).pushBack(5).print();

	MyVector<char> charV;
	charV.pushBack('A').pushBack('B').pushBack('C').pushBack('D').pushBack('E').print();

	MyVector<Circle> circleV;
	circleV.pushBack(Circle(1)).pushBack(Circle(2)).pushBack(Circle(3)).pushBack(Circle(4)).pushBack(Circle(5)).print();

	return 0;
}