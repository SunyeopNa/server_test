#include <iostream>
#include <string>

using namespace std;

class Circle
{
protected : 
	int radius;				// ���� ������

public : 
	Circle(int in_radius) // �� ������
		: radius(in_radius)
	{}
	int getRadius()	// ������ ��ȯ
	{
		return radius;
	}
};


// ���� �̸��� ������ �� �ִ� NamedCircle Class, Circle�� ��ӹ���
class NamedCircle : protected Circle
{
private : 
	string name;
public :
	NamedCircle(int in_radius, string in_name)
		: name(in_name), Circle(in_radius)
	{}
	void show()
	{
		cout << "�������� " << radius << "�� " << name << endl;
	}
	
};

int main()
{
	NamedCircle waffle(3, "waffle");
	waffle.show();
}

