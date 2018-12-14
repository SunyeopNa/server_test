#include <iostream>
#include <string>
#include <vector>
using namespace std;
class People
{
public:
	string name;
	People(string name) :name(name) {}
	~People() {}
	People() { name = ""; }
	bool operator > (const People& ref)
	{
		return name > ref.name;
	}
	bool operator == (const People& ref)
	{
		return name[0] == ref.name[0];
	}
	friend ostream& operator << (ostream& os, People &ref)
	{
		os << ref.name;
		return os;
	}
};


template <class T>
class SortedArray
{
	int size;
	T list[100];

public:
	SortedArray()
	{
		size = 0;
	}
	~SortedArray()
	{

	}
	SortedArray& insert(T element)
	{
		list[size++] = element;
		cout << "insert : " << element << endl;

		for (int i = 0; i < size; i++)
		{
			for (int j = i; j < size; j++)
			{
				if (list[i] == NULL || list[j] == NULL)
					break;

				else if (list[i] > list[j])
				{
					T element = list[i];
					list[i] = list[j];
					list[j] = element;
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << list[i] << " ";
		}cout << endl << endl;
		return *this;
	}
	

	SortedArray& remove(T element)
	{
		cout << "remove : " << element << endl;

		for (int i = 0; i < size; i++)
		{
			if (list[i] == element)
			{
				list[i] = NULL;
			}
			else if (list[i] == NULL)
			{

			}
			else
			{
				cout << list[i] << " ";
			}
		}
		cout << endl << endl;
		return *this;
	}
};


template <>
class SortedArray <People>
{
	int size;
	People list[100];

public:
	SortedArray()
	{
		size = 0;
	}
	~SortedArray()
	{

	}
	SortedArray& insert(People element)
	{
		list[size++] = element;
		cout << "insert : " << element << endl;

		for (int i = 0; i < size; i++)
		{
			for (int j = i; j < size; j++)
			{
				if (list[i] == People("NULL") || list[j] == People("NULL"))
					break;

				else if (list[i] > list[j])
				{
					People element = list[i];
					list[i] = list[j];
					list[j] = element;
				}
			}
		}

		for (int i = 0; i < size; i++)
		{
			cout << list[i] << " ";
		}cout << endl << endl;
		return *this;
	}


	SortedArray& remove(People element)
	{
		cout << "remove : " << element << endl;

		for (int i = 0; i < size; i++)
		{
			if (list[i] == element)
			{
				list[i] = People("NULL");
			}
			else if (list[i] == People("NULL"))
			{

			}
			else
			{
				cout << list[i] << " ";
			}
		}
		cout << endl << endl;
		return *this;
	}
};



int main()
{
	SortedArray<int> iSortedArray;

	iSortedArray
		.insert(2)
		.insert(1)
		.insert(4)
		.insert(6)
		.insert(5)
		.insert(2)
		.insert(5);

	iSortedArray.remove(2);
	iSortedArray.remove(5);

	SortedArray<People> pSortedArray;
	pSortedArray
		.insert(People("Alax"))
		.insert(People("Berry"))
		.insert(People("Mary"))
		.insert(People("Harry"))
		.insert(People("Eric"))
		.insert(People("Alonzo"))
		.insert(People("Edward"));

	pSortedArray.remove(People("Alax"));
	pSortedArray.remove(People("Edward"));


	

	return 0;
}