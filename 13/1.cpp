#include <iostream>
using namespace std;
class Exception {
public:
	int score;

	Exception() {

	}
	Exception(int s) {
		this->score = s;
	}
	void report() {
		// �߻��� ������ ���̽� �з�
		if (score > 100) {
			cout << "������ 100���� �ʰ��� �� �����ϴ�!" << endl;
		}
		else {
			cout << "������ 0�� �̸��� �� �����ϴ�!" << endl;
		}
	}
};
int main() {
	while (1) {
		int score;

		try {
			cout << "������ �Է��ϼ��� : ";
			cin >> score;
			if (score > 100 || score < 0) {
				//���� ó��
				throw Exception(score);
			}
			else if (score >= 90) {
				cout << "A" << endl;
			}
			else if (score >= 80) {
				cout << "B" << endl;
			}
			else if (score >= 70) {
				cout << "C" << endl;
			}
			else {
				cout << "D" << endl;
			}
		}
		catch (Exception &e) {
			//���� ���
			e.report();
		}
	}
}