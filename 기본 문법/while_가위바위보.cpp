// while문과 가위바위보 게임

#include <iostream>
#include <time.h>

using namespace std;

enum SRP {
	SRP_S = 1,		// 가위
	SRP_R,			// 바위
	SRP_P,			// 보
	SRP_END
};

int main() {
	/*
		반복문 : 특정 작업을 반복해서 수행해주는 기능이다.
		종류: for, while, do while 3종류가 존재한다.
	*/

	int iNumber = 0;
	while (iNumber < 10) {
		cout << iNumber << endl;
		++iNumber;

		if (iNumber == 4)
			break;
	}

	// 화면을 깨끗히 지워준다.
	system("cls");

	// 난수 테이블 생성
	srand((unsigned int)time(0));

	int iPlayer, iAI;

	while (true) {
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3. 보" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요: ";
		cin >> iPlayer;

		if (iPlayer < SRP_S || iPlayer > SRP_END) {
			cout << "잘못된 값을 입력하였습니다." << endl;
			//일시정지
			system("pause");
			// continue: 반복문의 시작점으로 이동시켜주는 기능이다.
			continue;
		}
		else if (iPlayer == SRP_END) {
			break;
		}
		
		// 봇이 선택을 한다.
		iAI = rand() % 3 + SRP_S;
		
		switch (iAI) {
		case SRP_S:
			cout << "AI: 가위" << endl;
			break;
		case SRP_R:
			cout << "AI: 바위" << endl;
			break;
		case SRP_P:
			cout << "AI: 보" << endl;
			break;
		}

		int iWin = iPlayer - iAI;

		if (iWin == 1 || iWin == -2) {
			cout << "Player 승리" << endl;
		}
		else if (iWin == 0) {
			cout << "비김" << endl;
		}
		else {
			cout << "AI 승리" << endl;
		}

		system("pause");
	}

	return 0;
}