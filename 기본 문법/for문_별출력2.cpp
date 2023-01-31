/*
	for문 연습 문제2
	별을 아래의 형태로 출력되게 한다.
	   *
	  ***
	 *****
	*******
*/

#include <iostream>

using namespace std;

int main() {

	for (int i = 0; i < 4; i++) {
		for (int j = 3-i; j > 0; j--) {
			cout << " ";
		}
		for (int j = 0; j<i*2+1; j++) {
			cout << "*";
		}
		
		for (int j = 3-i; j > 0; j--) {
			cout << " ";
		}
		cout << endl;
	}

	return 0;
}