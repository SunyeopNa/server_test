#include <iostream>

using namespace std;

class Engine
{
private:
	int horsepower;

public:
	Engine() : horsepower(200) {}
	Engine(const int &horsepower) : horsepower(horsepower) {}

	void SetHorsepower(int horsepower) 
	{
		this->horsepower = horsepower;
	}

	int GetHorsepower() 
	{
		return horsepower;
	}
};

class Wheel
{

};


class Car
{
private:

	Engine *engine;
	Wheel *wheel[4];

public:

	void setEngine(Engine *engine)
	{
		this->engine = engine; // 엔진 포인터에 매개변수로 들어온 포인터 대입
	}

	
	void setWheel(Wheel *wheel, const int &index)
	{
		this->wheel[index] = wheel;
	}

	void PrintEnginePower()
	{
		cout << "엔진의 마력은 : " << engine->GetHorsepower() << endl;
	}
};

int main()
{
	Car car;
	Engine *eng = new Engine();
	Wheel *wheel = new Wheel[4];

	car.setEngine(eng);
	for (int i = 0; i < 4; ++i)
	{
		car.setWheel(wheel + i, i);
	}

	car.PrintEnginePower();
}