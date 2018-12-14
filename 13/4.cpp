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
			cout << "송금자의 잔고가 적습니다." << endl;
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
			cout << "에러가 발생하여 원상복구됩니다." << endl;
		}
	}
};

int main() {
	Bank bank;
	People harry(1000);
	People potter(2000);

	// harry 가 potter 에게 송금
	bank.sendMoney(harry, potter, 1500);

	return 0;
}