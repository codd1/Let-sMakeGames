// 빙고게임을 함수로 변환

#include <iostream>
#include <time.h>

using namespace std;

enum AI_MODE {
	AM_EASY = 1,
	AM_HARD
};

enum LINE_NUMBER {
	LN_W1,		// LINE Width (=0~4)
	LN_W2,
	LN_W3,
	LN_W4,
	LN_W5,
	LN_H1,		// LINE Height (=5~9)
	LN_H2,
	LN_H3,
	LN_H4,
	LN_H5,
	LN_LT,		// LINE LeftTop (=10)
	LN_RT,		// LINE RightTop (=11)
};

// 함수는 선언과 정의 부분으로 나눌 수 있다.
void SetNumber(int* pArray);
void Shuffle(int* pArray);
AI_MODE SelectAIMode();
void OutputNumber(int* pArray, int bingo);
int BingoLineCheckWH(int* pArray, int bingo);
int BingoLineCheckD(int* pArray, int bingo);
void StoreStarValue(int* pArray, int* pAIArray, int input);
int SelectAINumber(int* pArray, AI_MODE eMode);

int main() {
	srand((unsigned int)time(0));

	// 배열에 1~25 값 저장
	int iNumber[25] = {};
	int iAINumber[25] = {};

	SetNumber(iNumber);
	SetNumber(iAINumber);

	// 배열 값 랜덤하게 섞기
	Shuffle(iNumber);
	Shuffle(iAINumber);

	int iBingo = 0, iAIbingo = 0;		// 총 빙고 수

	// AI 난이도를 선택한다.
	AI_MODE eAIMode = SelectAIMode();

	while (true) {
		system("cls");

		// 플레이어 5X5 빙고판 출력
		cout << "============= Player =============" << endl;
		OutputNumber(iNumber, iBingo);

		// AI 5X5 빙고판 출력
		cout << "============== AI ==============" << endl;
		// AI Mode 출력
		switch (eAIMode) {
		case AM_EASY:
			cout << "AI Mode: EASY" << endl;
			break;
		case AM_HARD:
			cout << "AI Mode: Hard" << endl;
			break;
		}
		OutputNumber(iAINumber, iAIbingo);


		// 변수 초기화
		iBingo = iAIbingo = 0;

		// 플레이어가 숫자를 입력하고, 입력 받은 숫자 위치에 별 모양(INT_MAX) 값 저장
		int input;
		cout << "숫자를 입력해주세요(1 ~ 25): ";
		cin >> input;

		if (input == 0) {
			break;
		}
		StoreStarValue(iNumber, iAINumber, input);

		// AI가 숫자를 선택한다. AI가 선택하는 것은 AI모드에 따라서 달라진다.
		input = SelectAINumber(iAINumber, eAIMode);
		// AI가 선택한 숫자 위치에 별 모양(INT_MAX) 값 저장
		StoreStarValue(iNumber, iAINumber, input);


		// 빙고 확인 - 플레이어
		iBingo = BingoLineCheckWH(iNumber, iBingo);
		iBingo = BingoLineCheckD(iNumber, iBingo);
		// 빙고 확인 - AI
		iAIbingo = BingoLineCheckWH(iAINumber, iAIbingo);
		iAIbingo = BingoLineCheckD(iAINumber, iAIbingo);


		// 종료 조건 확인 (빙고 5개 시 종료)
		if (iBingo >= 5) {
			cout << endl << "Player 승리" << endl;
			break;
		}
		else if (iAIbingo >= 5) {
			cout << endl << "AI 승리" << endl;
			break;
		}
	}

	cout << "빙고 게임이 종료되었습니다." << endl;

	return 0;
}


void SetNumber(int* pArray) {
	for (int i = 0; i < 25; i++) {
		pArray[i] = i + 1;
	}
}

void Shuffle(int* pArray) {
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		// 플레이어 배열 섞기
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = pArray[idx1];
		pArray[idx1] = pArray[idx2];
		pArray[idx2] = temp;
	}
}

AI_MODE SelectAIMode() {
	int iAIMode;

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

	return (AI_MODE)iAIMode;
}

void OutputNumber(int* pArray, int bingo) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (pArray[i * 5 + j] == INT_MAX) {
				cout << "*\t";
			}
			else {
				cout << pArray[i * 5 + j] << "\t";
			}
		}
		cout << endl;
	}
	cout << "Bingo Line: " << bingo << endl << endl;
}

int BingoLineCheckWH(int* pArray, int bingo) {
	int wLine = 0;
	int hLine = 0;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			// 가로 줄 확인
			if (pArray[i * 5 + j] == INT_MAX) {
				wLine++;
			}
			// 세로 줄 확인
			if (pArray[j * 5 + i] == INT_MAX) {
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

	return bingo;
}

int BingoLineCheckD(int* pArray, int bingo) {
	int dLine1 = 0;
	int dLine2 = 0;

	// 대각선 빙고 확인
	for (int i = 0; i < 25; i++) {
		// ↙ 대각선 확인
		if ((i != 0) && (i % 4 == 0) && (i < 24) && pArray[i] == INT_MAX) {
			dLine1++;
		}
		// ↘ 대각선 확인
		if ((i % 6 == 0) && pArray[i] == INT_MAX) {
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

	return bingo;
}

void StoreStarValue(int* pArray, int* pAIArray, int input) {
	for (int i = 0; i < 25; i++) {
		if (input == pArray[i]) {
			pArray[i] = INT_MAX;
		}
		if (input == pAIArray[i]) {
			pAIArray[i] = INT_MAX;
		}
	}
}

int SelectAINumber(int* pArray, AI_MODE eMode) {
	int iNoneSelect[25] = {};		// EASY 모드 AI가 선택할 숫자 목록
	int iNoneSelectCount = 0;
	int iAISelectNum = 0;

	// AI가 숫자를 선택한다. AI가 선택하는 것은 AI모드에 따라서 달라진다.
	switch (eMode) {
		/*
			AI Easy 모드는 현재 AI의 숫자 목록 중
			*로 바뀌지 않은 숫자 목록을 만들어서 그 목록 중 하나를 선택하게 한다. (랜덤하게)
		*/
	case AM_EASY:
		// 지금까지 선택 안된 숫자 목록을 만들어준다.
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; i++) {
			if (pArray[i] != INT_MAX) {
				iNoneSelect[iNoneSelectCount] = pArray[i];
				iNoneSelectCount++;
			}
		}
		// 남은 숫자 중 AI가 랜덤하게 선택한다.
		iAISelectNum = iNoneSelect[rand() % iNoneSelectCount];
		break;
	case AM_HARD:
		/*
			AI Hard 모드는 현재 숫자 중 빙고줄 완성 가능성이 가장 높은 줄을 찾아서
			그 줄에 있는 숫자 중 하나를 *로 만들어준다.
			가장 빙고가 빨리 만들어지는 라인을 찾아서 그 라인에 있는 숫자를 선택한다.
		*/
		int iLine = 0;
		int iStarCount = 0;
		int iSaveMaxCount = 0;		// *이 가장 많은 줄의 *의 갯수

		// 가로 라인에서 가장 *이 많은 라인을 찾는다.
		for (int i = 0; i < 5; i++) {
			iStarCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[i * 5 + j] == INT_MAX) {
					iStarCount++;
				}
			}
			if (iStarCount < 5 && iSaveMaxCount < iStarCount) {
				iLine = i;
				iSaveMaxCount = iStarCount;
			}
		}
		// 가로 라인과 세로 라인들을 비교해 별이 가장 많은 라인을 구한다.
		for (int i = 0; i < 5; i++) {
			iStarCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[j * 5 + i] == INT_MAX) {
					iStarCount++;
				}
			}
			if (iStarCount < 5 && iSaveMaxCount < iStarCount) {
				iLine = i + 5;		// 세로 라인은 5 ~ 9이므로 +5
				iSaveMaxCount = iStarCount;
			}
		}

		// ↘ 대각선 체크
		iStarCount = 0;
		for (int i = 0; i < 25; i += 6) {
			if (pArray[i] == INT_MAX) {
				iStarCount++;
			}
		}
		if (iStarCount < 5 && iSaveMaxCount < iStarCount) {
			iLine = LN_LT;
			iSaveMaxCount = iStarCount;
		}

		// ↙ 대각선 체크
		iStarCount = 0;
		for (int i = 4; i <= 20; i += 4) {
			if (pArray[i] == INT_MAX) {
				iStarCount++;
			}
		}
		if (iStarCount < 5 && iSaveMaxCount < iStarCount) {
			iLine = LN_RT;
			iSaveMaxCount = iStarCount;
		}

		// 모든 라인을 조사했으면 iLine에 가능성이 가장 높은 줄 번호가 저장된다.
		// AI가 그 줄에 있는 *이 아닌 숫자 중 하나를 선택
		if (iLine <= LN_W5) {		// 가능성이 높은 곳이 가로 줄 중 하나라면
			for (int i = 0; i < 5; i++) {
				if (pArray[iLine * 5 + i] != INT_MAX) {
					iAISelectNum = pArray[iLine * 5 + i];
					break;
				}
			}
		}
		else if (iLine <= LN_H5) {	// 가능성이 높은 곳이 세로 줄 중 하나라면
			for (int i = 0; i < 5; i++) {
				// LN_H1 ~ LN_H5가 5~9 이므로 iLine-5를 한다. 그러면 0~4가 됨.
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX) {
					iAISelectNum = pArray[i * 5 + (iLine - 5)];
					break;
				}
			}
		}
		else if (iLine == LN_LT) {	// 가능성이 높은 곳이 ↘ 대각선이라면
			for (int i = 0; i < 25; i += 6) {
				if (pArray[i] != INT_MAX) {
					iAISelectNum = pArray[i];
					break;
				}
			}
		}
		else if (iLine == LN_RT) {	// 가능성이 높은 곳이 ↙ 대각선이라면
			for (int i = 4; i <= 20; i += 4) {
				if (pArray[i] != INT_MAX) {
					iAISelectNum = pArray[i];
					break;
				}
			}
		}
		break;
	}

	return iAISelectNum;
}