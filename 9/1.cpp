#include <iostream>

using namespace std;

class Finger
{
private:
	int _length;

public:
	void SetLength(const int &length)
	{
		_length = length;
	}

	int GetLength()
	{
		return _length;
	}
};


class Hand
{
private:
	Finger *fingers; //손은 손가락 5개를 포함한다.

public:
	Hand()
	{
		fingers = new Finger[5]; 

		for (int i = 0; i < 5; ++i)
		{
			fingers[i].SetLength(i + 4); 
		}
	}

	~Hand()
	{
		delete[] fingers; 
	}

	void PrintFingers() 
	{
		for (int i = 0; i < 5; ++i)
		{
			cout << i << "번째 손가락의 길이 : " << fingers[i].GetLength() << endl;
		}
	}
};

int main()
{
	Hand hand;
	hand.PrintFingers();
}