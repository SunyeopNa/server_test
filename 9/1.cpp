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
	Finger *fingers; //���� �հ��� 5���� �����Ѵ�.

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
			cout << i << "��° �հ����� ���� : " << fingers[i].GetLength() << endl;
		}
	}
};

int main()
{
	Hand hand;
	hand.PrintFingers();
}