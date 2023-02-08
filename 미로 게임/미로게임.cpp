// 미로 게임

#include <iostream>
#include <conio.h>

using namespace std;

/*
	0: 벽
	1: 길
	2: 시작점
	3: 도착점
	4: 폭탄
*/

struct _tagPoint {
	int x;
	int y;
};

// typedef: 타입을 재정의하는 기능
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

#define BOMB_MAX 5

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos) {

	pStartPos->x = 0;
	pStartPos->y = 0;

	pEndPos->x = 19;
	pEndPos->y = 19;

	*pPlayerPos = *pStartPos;

	strcpy_s(Maze[0], "21100000000000000000");
	strcpy_s(Maze[1], "00111111111100000000");
	strcpy_s(Maze[2], "00100010000111111100");
	strcpy_s(Maze[3], "01100010000000000100");
	strcpy_s(Maze[4], "01000011110001111100");
	strcpy_s(Maze[5], "01000000001111000000");
	strcpy_s(Maze[6], "01100000001000000000");
	strcpy_s(Maze[7], "00100000001111111000");
	strcpy_s(Maze[8], "00000000000000001110");
	strcpy_s(Maze[9], "00000111111111111000");
	strcpy_s(Maze[10], "00111100000000000000");
	strcpy_s(Maze[11], "00001111100000000000");
	strcpy_s(Maze[12], "00000001111111000000");
	strcpy_s(Maze[13], "00011111000111111000");
	strcpy_s(Maze[14], "00010000000000110000");
	strcpy_s(Maze[15], "00010000000000011100");
	strcpy_s(Maze[16], "00011111100001110000");
	strcpy_s(Maze[17], "00000111110000000000");
	strcpy_s(Maze[18], "00001100011111011110");
	strcpy_s(Maze[19], "00000001110001110013");
}

void Output(char Maze[21][21], PPOINT pPlayerPos) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (Maze[i][j] == '4') {		// 폭탄
				cout << "♨";
			}
			else if (pPlayerPos->x == j && pPlayerPos->y == i) {	// 플레이어의 현재 위치
				cout << "☆";
			}
			else if (Maze[i][j] == '0') {	// 벽
				cout << "■";
			}
			else if (Maze[i][j] == '1') {	// 길
				cout << "  ";
			}
			else if (Maze[i][j] == '2') {	// 시작점
				cout << "★";
			}
			else if (Maze[i][j] == '3') {	// 도착점
				cout << "◎";
			}
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y - 1 >= 0) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0' && Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4') {
			pPlayerPos->y--;
		}
	}
}
void MoveDown(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y + 1 < 20) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0' && Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4') {
			pPlayerPos->y++;
		}
	}
}
void MoveRight(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x + 1 < 20) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0' && Maze[pPlayerPos->y][pPlayerPos->x + 1] != '4') {
			pPlayerPos->x++;
		}
	}
}
void MoveLeft(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x - 1 >= 0) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0' && Maze[pPlayerPos->y][pPlayerPos->x - 1] != '4') {
			pPlayerPos->x--;
		}
	}
}

void MovePlayer(char Maze[21][21], PPOINT pPlayerPos, char cInput) {
	switch (cInput) {
	case 'w':
	case 'W':
		MoveUp(Maze, pPlayerPos);
		break;
	case 's':
	case 'S':
		MoveDown(Maze, pPlayerPos);
		break;
	case 'a':
	case 'A':
		MoveLeft(Maze, pPlayerPos);
		break;
	case 'd':
	case 'D':
		MoveRight(Maze, pPlayerPos);
		break;
	}
}

// 포인터 변수를 const로 생성하면 가리키는 대상의 값을 변경할 수 없다.
void CreateBomb(char Maze[21][21], const PPOINT pPlayer, PPOINT pBombArr, int* pBombCount) {
	if (*pBombCount == BOMB_MAX) {
		return;
	}
	for (int i = 0; i < *pBombCount; i++) {
		// 폭탄이 설치된 위치에 폭탄 설치 불가
		if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y) {
			return;
		}
	}
	pBombArr[*pBombCount] = *pPlayer;
	(*pBombCount)++;

	Maze[pPlayer->y][pPlayer->x] = '4';
}

void Fire(char Maze[21][21], PPOINT pPlayer, PPOINT pBombArr, int* pBombCount) {
	for (int i = 0; i < *pBombCount; i++) {
		// 폭탄이 있던 자리도 터진다. (길이 된다)
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// 폭탄 기준 윗 칸 확인
		if (pBombArr[i].y - 1 >= 0) {
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0') {
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1) {
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		// 폭탄 기준 아랫 칸 확인
		if (pBombArr[i].y + 1 < 20) {
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0') {
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1) {
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		// 폭탄 기준 왼쪽 칸 확인
		if (pBombArr[i].x - 1 >= 0) {
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
		// 폭탄 기준 오른쪽 칸 확인
		if (pBombArr[i].x + 1 < 20) {
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = 0;
				pPlayer->y = 0;
			}
		}
	}
	// 폭탄 갯수 초기화
	*pBombCount = 0;
}


int main() {
	// 20X20 미로를 만든다.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	int iBombCount = 0;
	POINT tBombPos[BOMB_MAX];

	// 미로를 설정한다.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true) {
		system("cls");
		// 미로를 출력한다.
		Output(strMaze, &tPlayerPos);

		// 목적지에 도착했는지 확인
		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y) {
			cout << "도착했습니다." << endl;
			break;
		}

		cout << "T: 폭탄설치 / U: 폭탄 터트리기" << endl;
		cout << "W: 위 / S: 아래 / A: 왼쪽 / D: 오른쪽 / Q: 종료 ";

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}
		else if (cInput == 't' || cInput == 'T') {
			CreateBomb(strMaze, &tPlayerPos, tBombPos, &iBombCount);
		}
		else if (cInput == 'u' || cInput == 'U') {
			Fire(strMaze, &tPlayerPos, tBombPos, &iBombCount);
		}
		else {
			MovePlayer(strMaze, &tPlayerPos, cInput);
		}
	}

	return 0;
}