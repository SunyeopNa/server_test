#include <iostream>
using namespace std;

class Cat {

private:
	char *name;
	int age;

public:
	Cat(char *_name, int age) :age(age) {

		name = new char[strlen(_name) + 1];
		strcpy(name, _name);
	}
	Cat(Cat&& a) : name(a.name), age(a.age) {
		a.name = nullptr;
		a.age = NULL;

		cout << "Cat move constructor" << endl;
	}
	Cat& operator = (Cat &&a) {

		cout << "move assignment operator" << endl;

		if (&a == this) return *this;

		if (!name) delete name;
		if (!age) age = NULL;

		name = a.name;
		a.name = nullptr;

		age = a.age;
		a.age = NULL;

		return *this;
	}
	void print() {

		cout << "name : " << name << endl;
		cout << "age : " << age << endl;
	}
};

template<class T>
void MySwap(T &a, T &b) {

	// 깊은 복사를 통한 swap
	// T tmp = a;
	// a = b;
	// b = tmp;

	//std::move 를 통한 swap
	T tmp{ move(a) };
	a = move(b);
	b = move(tmp);

}

int main() {

	Cat cat1((char*)"Alice", 2);
	Cat cat2((char*)"Bobby", 3);

	cat1.print();
	cat2.print();
	cout << endl;

	MySwap(cat1, cat2);

	cout << endl;
	cat1.print();
	cat2.print();

	return 0;
}
