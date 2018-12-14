#include <iostream>
using namespace std;
class People  {
public:
	int money;
	People(int b) : money(b) {}
};

class Bank {

public:
	int money;
	Bank() {}
	Bank(int b) :money(b) {}

	void sendMoney(People &payer, People &payee, int money) {
		subMoney(payer, payee, money);
		addMoney(payer, payee, money);
	}
	void subMoney(People &payer, People &payee, int money) {
		try {
			if (payer.money < money) {
				throw - 1;
			}
			else {
				payer.money -= money;
			}
		}
		catch (const int &e) {
			cout << "�۱����� �ܰ� �����ϴ�." << endl;
		}
	}
	void addMoney(People &payer, People &payee, int money) {
		try {
			if (1) {
				throw - 1;
			}
			else {
				payee.money += money;
			}
		}
		catch (const int &e) {
			payer.money += money;
			cout << "������ �߻��Ͽ� ���󺹱��˴ϴ�." << endl;
		}
	}
};

int main() {
	Bank bank;
	People harry(1000);
	People potter(2000);

	// harry �� potter ���� �۱�
	bank.sendMoney(harry, potter, 1500);

	return 0;
}