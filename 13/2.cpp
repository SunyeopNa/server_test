#include <iostream>
using namespace std;

void devide(int op1, int op2) {
	try {
		if (op2 == 0) {
			throw - 1;
		}
		else {
			cout << op1 << " / " << op2 << " = " << op1 / op2;
		}
	}
	catch(const int &e) {
		//���� ó��
		cout << "0���� ���� �� �����ϴ�." << endl;
	}
}
int main() {
	devide(9,0);

	return 0;
}