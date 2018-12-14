#include <iostream>
using namespace std;

class Animal {
public:
	virtual void do_Eat() const = 0;
};

class Dog : public Animal {
public:
	void do_Eat() const override {
		cout << "Dog's eat()" << endl;
	}
};
class Cat : public Animal {
public:
	void do_Eat( ) const override {
		cout << "Cat's eat()" << endl;
	}
};
class Rabbit : public Animal {
public:
	void do_Eat() const override {
		cout << "Rabbit's eat()" << endl;
	}
};
void do_Eat(Animal *animal) {
	animal->do_Eat();
}

int main() {

	//Animal animal;
	Dog dog;
	Cat cat;
	Rabbit rabbit;

	do_Eat(&dog);
	do_Eat(&cat);
	do_Eat(&rabbit);

	return 0;
}
