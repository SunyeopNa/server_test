#include <iostream>
using namespace std;

class People {
public:
	People() { cout << "People 持失" << endl; }
	virtual ~People() { cout << "People 社瑚" << endl; }
};

class Parent : public People {
	
	string *children;

public:
	Parent() {
		children = new string[3];
		cout << "Parent 持失" << endl;
	}
	~Parent() {
		delete[] children;
		cout << "Parent 社瑚" << endl;
	}
};

int main() {
	
	Parent *parent = new Parent;
	People * people = parent;

	delete people;

	return 0;
}