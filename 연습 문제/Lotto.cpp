// 로또

#include <iostream>
#include <time.h>
using namespace std;

int main() {

	srand((unsigned int)time(0));
	// Lotto Program -> 중복되지 않는 1~45의 숫자 6개
	int iLotto[45] = {};

	// 1~45까지의 숫자를 배열에 차례대로 넣어준다.
	for (int i = 0; i < 45; i++) {
		iLotto[i] = i + 1;
	}

	// Shuffle (1~45까지 저장된 배열 전체를 100번정도 골고루 섞어준다.)
	// 배열의 값을 난수로 생성하는 것이 아니라 인덱스를 난수로 생성해 배열을 섞는 것이다.
	int iTemp, idx1, idx2;

	for (int i = 0; i < 100; i++) {

		// 0~44 사이의 난수
		idx1 = rand() % 45;
		idx2 = rand() % 45;

		iTemp = iLotto[idx1];
		iLotto[idx1] = iLotto[idx2];
		iLotto[idx2] = iTemp;
	}

	/*for (int i = 0; i < 45; i++) {
		cout << iLotto[i] << endl;
	}*/

	// 로또 추첨 번호 출력 (추첨 번호 6개 + 보너스 번호 1개)
	for (int i = 0; i < 6; i++) {
		cout << iLotto[i] << "\t";
	}
	cout << "보너스 번호: " << iLotto[6] << endl;

	return 0;
}