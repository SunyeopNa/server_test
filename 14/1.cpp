#include <iostream>
using namespace std;

class Resource {

public:
	int m_data[100];
	Resource() {

		cout << "Resource constructed" << endl;
	}
	~Resource() {

		cout << "REsource destroyed" << endl;
	}
};

template <class T>
class AutoPtr {

public :
	T *m_ptr = nullptr;

	AutoPtr(T *ptr = nullptr) :m_ptr(ptr) {

	}

	AutoPtr& operator = (AutoPtr &a) {

		if (&a == this) return *this;

		delete m_ptr;
		m_ptr = a.m_ptr;
		a.m_ptr = nullptr;
		return *this;
	}

	~AutoPtr() {
		if (m_ptr != nullptr) delete m_ptr;
	}
};
int main() {

	AutoPtr<Resource> res1(new Resource);
	AutoPtr<Resource> res2;

	cout << "res1 : " << res1.m_ptr << endl;
	cout << "res2 : " << res2.m_ptr << endl;

	res2 = res1;

	cout << "res1 : " << res1.m_ptr << endl;
	cout << "res2 : " << res2.m_ptr << endl;

}
