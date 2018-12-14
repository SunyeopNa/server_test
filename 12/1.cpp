#include <iostream>
#include <string>
using namespace std;

class Circle
{
	int radius;
public:
	Circle() {};
	Circle(int radius)	:radius(radius) {	}
	
	int getRadius()
	{
		return radius;
	}
	friend ostream& operator << (ostream& os, Circle& circle)
	{
		cout << "radius : " << circle.getRadius() << endl;
		return os;
	}
};

template <class T>
T* concat(T listA[], int sizeA, T listB[], int sizeB)
{
	T* result = new T[sizeA + sizeB];

	for (int i = 0; i < sizeA; i++)
		result[i] = listA[i];

	for (int i = 0; i < sizeB; i++)
		result[i + sizeA] = listB[i];

	return result;
}

template <class T>
void printList(T list[], int size)
{
	for (int i = 0; i < size; i++)
		cout << list[i];
	cout << endl;
}


template <>
void printList(char list[], int size)
{
	for (int i = 0; i < size; i++)
		cout << list[i] << " ";
	cout << endl;
}


int main()
{
	int iListA[] = { 1, 2, 3 };
	int iListB[] = { 4, 5, 6 };
	int *intResult = concat <int>(iListA, 3, iListB, 3);

	char cListA[] = { 'A', 'B', 'C' };
	char cListB[] = { 'D', 'E', 'F' };
	char *charResult = concat <char>(cListA, 3, cListB, 3);

	Circle circleListA[] = { Circle(1), Circle(2), Circle(3) };
	Circle circleListB[] = { Circle(4), Circle(5), Circle(6) };
	Circle *circleResult = concat <Circle>(circleListA, 3, circleListB, 3);

	printList(intResult, 6);
	printList(charResult, 6);
	printList(circleResult, 6);

	return 0;
}