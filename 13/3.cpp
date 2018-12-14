#include <iostream>
#include <string>
using namespace std;

class Exception {
public:
	int err_case;

	Exception() {}
	Exception(int c) {
		this->err_case = c;
	}

	void report() {
		switch (err_case) {
		case 1:
			cout << "Id is too short!" << endl; break;
		case 2:
			cout << "Id is too long!" << endl; break;
		case 3:
			cout << "Id is not composed of numbers only!" << endl; break;
		case 4:
			cout << "Password can't contain uppercase letters!" << endl; break;
		case 5:
			cout << "Password should consist of only lowercase letters, numbers, and special characters!" << endl; break;
		case 6:
			cout << "Password doesn't contain lowercase characters!" << endl; break;
		case 7:
			cout << "Password doesn't contain special characters!" << endl; break;
		case 8:
			cout << "Password doesn't contain numbers!" << endl; break;
		case 9:
			cout << "Password is too short!" << endl; break;
		case 10:
			cout << "Password is too long!" << endl; break;
		
		}
	}
};

void login(string id, string password) {
	int lower = 0, upper = 0, special = 0, number = 0;
	try {
		if (id.size() < 8) {
			throw Exception(1);
		}
		else if (id.size() > 10) {
			throw Exception(2);
		}
		for (int i = 0; i < id.size(); i++) {
			if (id[i] < '0' || id[i] >'9') {
				throw Exception(3);
			}
		}
		for (int i = 0; i < password.size(); i++) {
			if (password[i] >= 'a' && password[i] <= 'z') {
				lower++;
			}
			else if (password[i] >= '0' && password[i] <= '9') {
				number++;
			}
			else if (password[i] >= 'A' && password[i] <= 'Z') {
				throw Exception(4);
			}
			else {
				switch (password[i]) {
				case'!': case'@': case'#': case'$': case'%':
				case'^': case'&': case'*': case'(': case')':
					special++;
					break;
				default:
					cout << password[i] << endl;
					throw Exception(5);
				}
			}
		}
		if (lower == 0) {
			throw Exception(6);
		}
		else if (special == 0) {
			throw Exception(7);
		}
		else if (number == 0) {
			throw Exception(8);
		}
		if (password.size() < 8) {
			throw Exception(9);
		}
		else if (password.size() > 16) {
			throw Exception(10);
		}
	}
	catch (Exception &e) {
		e.report();
	}
}
int main() {
	while (1) {
		string id, pw;
		cout << "Id, Password : ";
		cin >> id >> pw;

		login(id, pw);
	}
	return 0;
}