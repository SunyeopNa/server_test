#include <iostream>
#include <vector>
using namespace std;

class People {
	
public:
	virtual void showInfo() { cout << "I'm People" << endl; }
};

class Engineer: public People {

public:
	void showInfo() { cout << "I'm Police" << endl; }
};

class Designer : public People {

public:
	void showInfo() { cout << "I'm Designer" << endl; }
};

class Director : public People {

public:
	void showInfo() { cout << "I'm Director" << endl; }
};

int main() {
	Engineer engineer;
	Designer designer;
	Director director;

	vector <reference_wrapper<People>> myTeam;
	myTeam.push_back(engineer);
	myTeam.push_back(designer);
	myTeam.push_back(director);

	for (auto &element : myTeam) {
		element.get().showInfo();
	}

	return 0;
}