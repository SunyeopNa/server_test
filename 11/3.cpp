#include <iostream>
#include <string>
using namespace std;

class Animal {

public:
	string name;
	void eat() { cout << "Animal's Eat" << endl; }
};

class Tiger : virtual public Animal {};

class Lion : virtual public Animal {};

class Liger : public Tiger, Lion {};

int main() {

	Liger liger;
	liger.eat();
	liger.name = "liger";

	return 0;
}