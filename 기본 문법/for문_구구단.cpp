// for문 연습 문제1
// 구구단을 2단부터 9단까지 출력하는 중첩 for문을 만들어보자.

#include <iostream>

using namespace std;

int main() {
	
	for (int i = 2; i < 10; i++) {
		for (int j = 1; j < 10; j++) {
			cout << i << " * " << j << " = " << i * j << endl;
		}
	}

	return 0;
}