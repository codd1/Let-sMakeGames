// 숫자 퍼즐 게임

#include <iostream>
#include <time.h>

// console input output 헤더파일.
// 콘솔창에서 입출력하는 기능들을 제공해준다.
#include <conio.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	
	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	// 가장 마지막 칸은 공백으로 비워둔다.
	// 공백을 의미하는 값으로 특수한 값인 INT_MAX라는 값을 사용할 것이다.

	iNumber[24] = INT_MAX;

	// 별이 있는 위치를 저장할 변수를 만들어준다.
	int iStarIndex = 24;		// 인덱스 번호

	// 마지막 공백을 제외하고 1 ~ 24 까지의 숫자만 섞어준다.
	// 즉 인덱스는 0 ~ 23번 인덱스까지만 섞어준다.
	int temp, idx1, idx2;

	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 24;
		idx2 = rand() % 24;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	while (true) {
		system("cls");

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX) {
					cout << "*" << "\t";
				}
				else {
					cout << iNumber[i * 5 + j] << "\t";
				}
			}
			cout << endl;
		}

		bool bWin = true;
		// 퍼즐을 맞추었는지 확인한다.
		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}
		if (bWin == true) {
			cout << "성공!!!" << endl;
			break;
		}

		cout << "W: 위 / S: 아래 / A: 왼쪽 / D: 오른쪽 / Q: 종료" << endl;

		// _getch() 함수는 문자 1개를 입력받는 함수이다.
		// 이 함수는 Enter를 치지 않더라도 문자를 누르는 순간 그 문자를 반환하고 종료
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}

		switch (cInput) {
		case 'w':
		case 'W':
			if (iStarIndex > 4) {	// 맨 윗 줄이 아닐 경우
				// 윗 칸의 인덱스로 교환
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20) {	// 맨 아랫 줄이 아닐 경우
				iNumber[iStarIndex] = iNumber[iStarIndex + 5];
				iNumber[iStarIndex + 5] = INT_MAX;
				iStarIndex += 5;
			}
			break;
		case 'a':
		case 'A':
			if (iStarIndex % 5 != 0) {
				iNumber[iStarIndex] = iNumber[iStarIndex - 1];
				iNumber[iStarIndex - 1] = INT_MAX;
				iStarIndex -= 1;
			}
			break;
		case 'd':
		case 'D':
			if (iStarIndex % 5 != 4) {
				iNumber[iStarIndex] = iNumber[iStarIndex + 1];
				iNumber[iStarIndex + 1] = INT_MAX;
				iStarIndex += 1;
			}
			break;
		}

	}
	
	cout << "게임을 종료합니다." << endl;


	return 0;
}