// 미로 게임 파일연동

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
	// MazeList.txt 파일을 읽어와서 미로 목록을 만든다.
	FILE* pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	char** pMazeList = NULL;

	if (pFile) {
		char cCount;

		fread(&cCount, 1, 1, pFile);
		
		// atoi: 아스키코드를 정수로 변환해준다.
		int iMazeCount = atoi(&cCount);

		// 다음 줄로 바뀌므로 한 글자 더 읽는다.
		fread(&cCount, 1, 1, pFile);

		// char* 배열을 미로 갯수만큼 할당한다.
		pMazeList = new char* [iMazeCount];

		for (int i = 0; i < iMazeCount; i++) {
			int iNameCount = 0;

			// 현재 미로의 파일 이름을 저장할 배열을 256개로 할당한다. (미리 넉넉하게 할당)
			pMazeList[i] = new char[256];

			while (true) {
				fread(&cCount, 1, 1, pFile);

				if (cCount != '\n') {
					pMazeList[i][iNameCount] = cCount;
					iNameCount++;
				}
				else {
					break;
				}
			}
			// 파일 이름을 모두 읽었다면 문자열의 마지막에 0을 넣어서 이 문자열의 끝을 알려준다.
			pMazeList[i][iNameCount] = 0;
		}

		fclose(pFile);

		// 읽을 파일 목록이 만들어졌으므로 각 파일중 하나를 선택해 선택한 미로를 읽어와서 설정한다.
		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}
		cout << "미로를 선택하세요: ";
		int iSelect;
		cin >> iSelect;

		// 선택한 미로 파일을 읽는다.
		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile) {
			// 미로의 세로 줄 수만큼 반복하며 한 줄씩 읽어온다.
			for (int i = 0; i < 20; i++) {
				fread(Maze[i], 1, 20, pFile);

				// 현재 줄의 미로를 검사해 시작점, 혹은 도착점이 있는지 확인한다.
				for (int j = 0; j < 20; j++) {
					if (Maze[i][j] == '2') {	// 시작점일 경우
						pStartPos->x = j;
						pStartPos->y = i;

						*pPlayerPos = *pStartPos;
					}
					else if (Maze[i][j] == '3') {	// 도착점일 경우
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				// 개행문자를 읽는다.
				fread(&cCount, 1, 1, pFile);
			}

			fclose(pFile);
		}
	}
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

void Fire(char Maze[21][21], PPOINT pPlayer, PPOINT pStartPost, PPOINT pBombArr, int* pBombCount) {
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
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// 폭탄 기준 아랫 칸 확인
		if (pBombArr[i].y + 1 < 20) {
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0') {
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// 폭탄 기준 왼쪽 칸 확인
		if (pBombArr[i].x - 1 >= 0) {
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// 폭탄 기준 오른쪽 칸 확인
		if (pBombArr[i].x + 1 < 20) {
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
			}
			// 플레이어가 폭탄에 맞았을 때 시작점으로 보낸다.
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
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
		cout << "W: 위 / S: 아래 / A: 왼쪽 / D: 오른쪽 / Q: 종료";

		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}
		else if (cInput == 't' || cInput == 'T') {
			CreateBomb(strMaze, &tPlayerPos, tBombPos, &iBombCount);
		}
		else if (cInput == 'u' || cInput == 'U') {
			Fire(strMaze, &tPlayerPos, &tStartPos, tBombPos, &iBombCount);
		}
		else {
			MovePlayer(strMaze, &tPlayerPos, cInput);
		}
	}

	return 0;
}