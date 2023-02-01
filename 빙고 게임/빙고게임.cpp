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

enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};

int main() {
	srand((unsigned int)time(0));

	// 배열에 1~25 값 저장
	int iNumber[25] = {};
	int iAINumber[25] = {};

	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// 배열 값 랜덤하게 섞기
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		// 플레이어 배열 섞기
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;

		// AI 배열 섞기
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = temp;

	}

	int bingo = 0, AIbingo = 0;		// 총 빙고 수
	int wLine, hLine, dLine1, dLine2;		// 플레이어의 가로 줄, 세로 줄, 대각선줄2개
	int wAILine, hAILine, dAILine1, dAILine2;	// AI의 ~~

	int iAIMode;

	int iNoneSelect[25] = {};		// EASY 모드 AI가 선택할 숫자 목록
	int iNoneSelectCount = 0;

	// AI 난이도를 선택한다.
	while (true) {
		system("cls");

		cout << "1. Easy" << endl;
		cout << "2. Hard" << endl;
		cout << "AI 모드를 선택하세요: ";

		cin >> iAIMode;

		if (iAIMode == AM_EASY || iAIMode == AM_HARD) {
			break;
		}
	}

	while (true) {
		system("cls");

		// 플레이어 5X5 빙고판 출력
		cout << "============= Player =============" << endl;
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
		cout << "Bingo Line: " << bingo << endl << endl;


		// AI 5X5 빙고판 출력
		cout << "============== AI ==============" << endl;
		// AI Mode 출력
		switch (iAIMode) {
		case AM_EASY:
			cout << "AI Mode: EASY" << endl;
			break;
		case AM_HARD:
			cout << "AI Mode: Hard" << endl;
			break;
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (iAINumber[i * 5 + j] == INT_MAX) {
					cout << "*\t";
				}
				else {
					cout << iAINumber[i * 5 + j] << "\t";
				}
			}
			cout << endl;
		}
		cout << "AI Bingo Line: " << AIbingo << endl << endl;


		// 변수 초기화
		bingo = wLine = hLine = dLine1 = dLine2 = 0;
		AIbingo = wAILine = hAILine = dAILine1 = dAILine2 = 0;

		// 플레이어가 숫자를 입력하고, 입력 받은 숫자 위치에 별 모양(INT_MAX) 값 저장
		int input;
		cout << "숫자를 입력해주세요(1 ~ 25): ";
		cin >> input;

		if (input == 0) {
			break;
		}

		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				iNumber[i] = INT_MAX;
			}
			if (input == iAINumber[i]) {
				iAINumber[i] = INT_MAX;
			}
		}

		// AI가 숫자를 선택한다. AI가 선택하는 것은 AI모드에 따라서 달라진다.
		switch (iAIMode) {
			/*
				AI Easy 모드는 현재 AI의 숫자 목록 중
				*로 바뀌지 않은 숫자 목록을 만들어서 그 목록 중 하나를 선택하게 한다. (랜덤하게)
			*/
		case AM_EASY:
			// 지금까지 선택 안된 숫자 목록을 만들어준다.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; i++) {
				if (iAINumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					iNoneSelectCount++;
				}
			}
			// 남은 숫자 중 AI가 랜덤하게 선택한다.
			input = iNoneSelect[rand() % iNoneSelectCount];
			break;
		case AM_HARD:
			break;
		}

		// AI가 선택한 숫자 위치에 별 모양(INT_MAX) 값 저장
		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				iNumber[i] = INT_MAX;
			}
			if (input == iAINumber[i]) {
				iAINumber[i] = INT_MAX;
			}
		}



		// 빙고 확인 - 플레이어

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
			}
			if (wLine == 5) {		// 가로 줄 빙고 확인
				//cout << "가로 줄 빙고" << endl;
				bingo++;
			}
			if (hLine == 5) {		// 세로 줄 빙고 확인
				//cout << "세로 줄 빙고" << endl;
				bingo++;
			}
			wLine = 0;
			hLine = 0;
		}
		// 대각선 빙고 확인
		for (int i = 0; i < 25; i++) {
			// ↙ 대각선 확인
			if ((i != 0) && (i % 4 == 0) && (i < 24) && iNumber[i] == INT_MAX) {
				dLine1++;
			}
			// ↘ 대각선 확인
			if ((i % 6 == 0) && iNumber[i] == INT_MAX) {
				dLine2++;
			}
		}
		if (dLine1 == 5) {
			//cout << "↙ 대각선 빙고" << endl;
			bingo++;
		}
		if (dLine2 == 5) {
			//cout << "↘ 대각선 빙고" << endl;
			bingo++;
		}


		// 빙고 확인 - AI

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				// 가로 줄 확인
				if (iAINumber[i * 5 + j] == INT_MAX) {
					wAILine++;
				}
				// 세로 줄 확인
				if (iAINumber[j * 5 + i] == INT_MAX) {
					hAILine++;
				}
			}
			if (wAILine == 5) {		// 가로 줄 빙고 확인
				AIbingo++;
			}
			if (hAILine == 5) {		// 세로 줄 빙고 확인
				AIbingo++;
			}
			wAILine = 0;
			hAILine = 0;
		}
		// 대각선 빙고 확인
		for (int i = 0; i < 25; i++) {
			// ↙ 대각선 확인
			if ((i != 0) && (i % 4 == 0) && (i < 24) && iAINumber[i] == INT_MAX) {
				dAILine1++;
			}
			// ↘ 대각선 확인
			if ((i % 6 == 0) && iAINumber[i] == INT_MAX) {
				dAILine2++;
			}
		}
		if (dAILine1 == 5) {
			AIbingo++;
		}
		if (dAILine2 == 5) {
			AIbingo++;
		}



		// 종료 조건 확인 (빙고 5개 시 종료)
		if (bingo >= 5) {
			cout << endl << "Player 승리" << endl;
			break;
		}
		else if (AIbingo >= 5) {
			cout << endl << "AI 승리" << endl;
			break;
		}

	}

	cout << "빙고 게임이 종료되었습니다." << endl;

	return 0;
}