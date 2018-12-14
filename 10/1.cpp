#include <iostream>
#include <string>

using namespace std;

class Circle
{
protected : 
	int radius;				// 원의 반지름

public : 
	Circle(int in_radius) // 원 생성자
		: radius(in_radius)
	{}
	int getRadius()	// 반지름 반환
	{
		return radius;
	}
};


// 원에 이름을 저장할 수 있는 NamedCircle Class, Circle을 상속받음
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
		cout << "반지름이 " << radius << "인 " << name << endl;
	}
	
};

int main()
{
	NamedCircle waffle(3, "waffle");
	waffle.show();
}

