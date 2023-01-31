// for문과 중첩for문

#include <iostream>

using namespace std;

int main() {
	// for문

	for (int i = 0; i < 10; i++) {
		cout << i << endl;
	}

	// 구구단 2단 출력
	for (int i = 1; i <= 9; i++) {
		cout << "2 * " << i << " = " << 2 * i << endl;
	}

	// 1~100 사이의 숫자 중 짝수만 출력하는 for문
	for (int i = 2; i <= 100; i=i+2) {
		cout << i << endl;
	}

	// 1~100 사이의 숫자 중 3과 7의 공배수만 출력하는 for문
	for (int i = 1; i <= 100; i++) {
		if (i % 21 == 0) {	// i % 3 == 0 && i % 7 == 0
			cout << i << endl;
		}
	}

	// 중첩 for문: for문 안에 또 다른 for문이 존재하는 형태
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "i = " << i << " j = " << j << endl;
		}
	}

	return 0;
}