/*
	빙고게임
	숙제: 숫자빙고게임을 만들어보자.
	1~25까지의 숫자가 있고 이 숫자를 골고루 섞어서 5x5로 출력한다.
	플레이어는 숫자를 입력받는다. 1~25 사이의 숫자를 입력받아야한다.
	0을 입력하면 게임을 종료한다.

	숫자를 입력받았으면 숫자목록 중 입력받은 숫자를 찾아서 *로 만들어준다.
	숫자를 *로 만든 후에 빙고 줄 수를 체크한다. 5x5이기 때문에 가로 5줄, 세로 5줄, 대각선 2줄이 나올 수 있다.
	빙고줄이 몇 줄인지를 체크해서 화면에 보여준다.
	5줄 이상일 경우 게임을 종료한다.
*/

#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	// 배열에 1~25 값 저장
	int iNumber[25] = {};
	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
	}

	// 배열 값 랜덤하게 섞기
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	int bingo = 0;	// 총 빙고 수
	int wLine = 0;	// 가로 줄 (5라면 가로 한 줄 완성)
	int hLine = 0;	// 세로 줄 (5라면 세로 한 줄 완성)
	int dLine1 = 0;	// 대각선 줄 (5라면 대각선 한 줄 완성)
	int dLine2 = 0;

	while (true) {
		system("cls");

		// 빙고판 출력
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iNumber[i * 5 + j] == INT_MAX) {
					cout << "*\t";
				}
				else {
					cout << iNumber[i * 5 + j] << "\t";
				}
			}
			cout << endl;
		}

		// 플레이어에게 입력 받고 입력 받은 숫자 별 모양(INT_MAX) 값 저장
		int input;
		cin >> input;

		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				iNumber[i] = INT_MAX;
			}
		}


		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				// 가로 줄 확인
				if (iNumber[i * 5 + j] == INT_MAX) {
					wLine++;
				}
				// 세로 줄 확인
				if (iNumber[j * 5 + i] == INT_MAX) {
					hLine++;
				}
				// 대각선 ↙ 줄 별 갯수 확인
				if ((i * 5 + j) != 0 && ((i * 5 + j) % 4) == 0 && iNumber[i * 5 + j] == INT_MAX) {
					dLine1++;
				}
				// 대각선 ↘ 줄 별 갯수 확인
				if (((i * 5 + j) % 6) == 0 && iNumber[i * 5 + j] == INT_MAX) {
					dLine2++;
				}
			}
			if (wLine == 5) {		// 가로 줄 빙고 확인
				bingo++;
			}
			if (hLine == 5) {		// 세로 줄 빙고 확인
				bingo++;
			}
			hLine = 0;
			wLine = 0;
		}

		// 대각선 빙고 확인
		if (dLine1 == 5) {
			bingo++;
		}
		if (dLine2 == 5) {
			bingo++;
		}

		// 종료 조건 확인 (빙고 5개 시 종료)
		if (bingo == 5) {
			cout << "Clear!!!" << endl;
			break;
		}

		// 변수 초기화
		bingo = 0;
		dLine1 = 0;
		dLine2 = 0;
	}

	cout << "빙고 게임이 종료되었습니다." << endl;

	return 0;
}