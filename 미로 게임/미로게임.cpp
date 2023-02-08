// 미로 게임

#include <iostream>
#include <conio.h>

using namespace std;

/*
	0: 벽
	1: 길
	2: 시작점
	3: 도착점
*/

struct _tagPoint {
	int x;
	int y;
};

// typedef: 타입을 재정의하는 기능
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

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
			if (pPlayerPos->x == j && pPlayerPos->y == i) {
				cout << "☆";
			}
			else if (Maze[i][j] == '0') {
				cout << "■";
			}
			else if (Maze[i][j] == '1') {
				cout << "  ";
			}
			else if (Maze[i][j] == '2') {
				cout << "★";
			}
			else if (Maze[i][j] == '3') {
				cout << "◎";
			}
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y - 1 >= 0) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0') {
			pPlayerPos->y--;
		}
	}
}
void MoveDown(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y + 1 < 20) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0') {
			pPlayerPos->y++;
		}
	}
}
void MoveRight(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x + 1 < 20) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0') {
			pPlayerPos->x++;
		}
	}
}
void MoveLeft(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x - 1 >= 0) {
		// 벽인지 체크한다.
		if (Maze[pPlayerPos->y][pPlayerPos->x - 1] != '0') {
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


int main() {
	// 20X20 미로를 만든다.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

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

		cout << "W: 위 / S: 아래 / A: 왼쪽 / D: 오른쪽 / Q: 종료 ";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}

		MovePlayer(strMaze, &tPlayerPos, cInput);
	}

	return 0;
}