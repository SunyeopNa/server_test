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
		// 발생한 예외의 케이스 분류
		if (score > 100) {
			cout << "점수는 100점을 초과할 수 없습니다!" << endl;
		}
		else {
			cout << "점수는 0점 미만일 수 없습니다!" << endl;
		}
	}
};
int main() {
	while (1) {
		int score;

		try {
			cout << "점수를 입력하세요 : ";
			cin >> score;
			if (score > 100 || score < 0) {
				//예외 처리
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
			//예외 출력
			e.report();
		}
	}
}