#include <iostream>
#include <string>
using namespace std;

class Person {
	string name;
	weak_ptr<Person> partner;

public :
	
	Person(const string &name) : name(name) {

		cout << name << " created" << endl;
	}
	~Person() {
		
		cout << name << " destroyed" << endl;
	}

	friend bool partnerUp(shared_ptr<Person> &p1, shared_ptr<Person> &p2) {

		if (!p1 || !p2) return false;

		p1->partner = p2;;
		p2->partner = p1;;

		cout << p1->name << "is partnered with " << p2->name << endl;

		return true;
	}

	shared_ptr<Person> getPartner() {

		return partner;
	}

	string &getName() {

		return name;
	}
};

int main()
{
	auto eric = make_shared<Person>("eric");
	auto paul = make_shared<Person>("paul");

	partnerUp(eric, paul);

	cout << eric->getPartner()->getName() << endl;
}