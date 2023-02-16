// �̷� ����

#include <iostream>
#include <conio.h>

using namespace std;

/*
	0: ��
	1: ��
	2: ������
	3: ������
	4: ��ź
*/

struct _tagPoint {
	int x;
	int y;
};

// typedef: Ÿ���� �������ϴ� ���
typedef _tagPoint POINT;
typedef _tagPoint* PPOINT;

#define BOMB_MAX 5

void SetMaze(char Maze[21][21], PPOINT pPlayerPos, PPOINT pStartPos, PPOINT pEndPos) {
	// MazeList.txt ������ �о�ͼ� �̷� ����� �����.
	FILE* pFile = NULL;

	fopen_s(&pFile, "MazeList.txt", "rt");

	char** pMazeList = NULL;

	if (pFile) {
		char cCount;

		fread(&cCount, 1, 1, pFile);
		
		// atoi: �ƽ�Ű�ڵ带 ������ ��ȯ���ش�.
		int iMazeCount = atoi(&cCount);

		// ���� �ٷ� �ٲ�Ƿ� �� ���� �� �д´�.
		fread(&cCount, 1, 1, pFile);

		// char* �迭�� �̷� ������ŭ �Ҵ��Ѵ�.
		pMazeList = new char* [iMazeCount];

		for (int i = 0; i < iMazeCount; i++) {
			int iNameCount = 0;

			// ���� �̷��� ���� �̸��� ������ �迭�� 256���� �Ҵ��Ѵ�. (�̸� �˳��ϰ� �Ҵ�)
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
			// ���� �̸��� ��� �о��ٸ� ���ڿ��� �������� 0�� �־ �� ���ڿ��� ���� �˷��ش�.
			pMazeList[i][iNameCount] = 0;
			
			//cout << pMazeList[i] << endl;
		}

		fclose(pFile);

		// ���� ���� ����� ����������Ƿ� �� ������ �ϳ��� ������ ������ �̷θ� �о�ͼ� �����Ѵ�.
		for (int i = 0; i < iMazeCount; i++) {
			cout << i + 1 << ". " << pMazeList[i] << endl;
		}
		cout << "�̷θ� �����ϼ���: ";
		int iSelect;
		cin >> iSelect;

		// ������ �̷� ������ �д´�.
		fopen_s(&pFile, pMazeList[iSelect - 1], "rt");

		if (pFile) {
			// �̷��� ���� �� ����ŭ �ݺ��ϸ� �� �پ� �о�´�.
			for (int i = 0; i < 20; i++) {
				fread(Maze[i], 1, 20, pFile);

				// ���� ���� �̷θ� �˻��� ������, Ȥ�� �������� �ִ��� Ȯ���Ѵ�.
				for (int j = 0; j < 20; j++) {
					if (Maze[i][j] == '2') {	// �������� ���
						pStartPos->x = j;
						pStartPos->y = i;

						*pPlayerPos = *pStartPos;
					}
					else if (Maze[i][j] == '3') {	// �������� ���
						pEndPos->x = j;
						pEndPos->y = i;
					}
				}

				// ���๮�ڸ� �д´�.
				fread(&cCount, 1, 1, pFile);
			}

			fclose(pFile);
		}
	}

	/*pStartPos->x = 0;
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
	strcpy_s(Maze[19], "00000001110001110013");*/
}

void Output(char Maze[21][21], PPOINT pPlayerPos) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (Maze[i][j] == '4') {		// ��ź
				cout << "��";
			}
			else if (pPlayerPos->x == j && pPlayerPos->y == i) {	// �÷��̾��� ���� ��ġ
				cout << "��";
			}
			else if (Maze[i][j] == '0') {	// ��
				cout << "��";
			}
			else if (Maze[i][j] == '1') {	// ��
				cout << "  ";
			}
			else if (Maze[i][j] == '2') {	// ������
				cout << "��";
			}
			else if (Maze[i][j] == '3') {	// ������
				cout << "��";
			}
		}
		cout << endl;
	}
}

void MoveUp(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y - 1 >= 0) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y - 1][pPlayerPos->x] != '0' && Maze[pPlayerPos->y - 1][pPlayerPos->x] != '4') {
			pPlayerPos->y--;
		}
	}
}
void MoveDown(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->y + 1 < 20) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y + 1][pPlayerPos->x] != '0' && Maze[pPlayerPos->y + 1][pPlayerPos->x] != '4') {
			pPlayerPos->y++;
		}
	}
}
void MoveRight(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x + 1 < 20) {
		// ������ üũ�Ѵ�.
		if (Maze[pPlayerPos->y][pPlayerPos->x + 1] != '0' && Maze[pPlayerPos->y][pPlayerPos->x + 1] != '4') {
			pPlayerPos->x++;
		}
	}
}
void MoveLeft(char Maze[21][21], PPOINT pPlayerPos) {
	if (pPlayerPos->x - 1 >= 0) {
		// ������ üũ�Ѵ�.
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

// ������ ������ const�� �����ϸ� ����Ű�� ����� ���� ������ �� ����.
void CreateBomb(char Maze[21][21], const PPOINT pPlayer, PPOINT pBombArr, int* pBombCount) {
	if (*pBombCount == BOMB_MAX) {
		return;
	}
	for (int i = 0; i < *pBombCount; i++) {
		// ��ź�� ��ġ�� ��ġ�� ��ź ��ġ �Ұ�
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
		// ��ź�� �ִ� �ڸ��� ������. (���� �ȴ�)
		Maze[pBombArr[i].y][pBombArr[i].x] = '1';

		// ��ź ���� �� ĭ Ȯ��
		if (pBombArr[i].y - 1 >= 0) {
			if (Maze[pBombArr[i].y - 1][pBombArr[i].x] == '0') {
				Maze[pBombArr[i].y - 1][pBombArr[i].x] = '1';
			}
			// �÷��̾ ��ź�� �¾��� �� ���������� ������.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y - 1) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// ��ź ���� �Ʒ� ĭ Ȯ��
		if (pBombArr[i].y + 1 < 20) {
			if (Maze[pBombArr[i].y + 1][pBombArr[i].x] == '0') {
				Maze[pBombArr[i].y + 1][pBombArr[i].x] = '1';
			}
			// �÷��̾ ��ź�� �¾��� �� ���������� ������.
			if (pPlayer->x == pBombArr[i].x && pPlayer->y == pBombArr[i].y + 1) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// ��ź ���� ���� ĭ Ȯ��
		if (pBombArr[i].x - 1 >= 0) {
			if (Maze[pBombArr[i].y][pBombArr[i].x - 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x - 1] = '1';
			}
			// �÷��̾ ��ź�� �¾��� �� ���������� ������.
			if (pPlayer->x == pBombArr[i].x - 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
		// ��ź ���� ������ ĭ Ȯ��
		if (pBombArr[i].x + 1 < 20) {
			if (Maze[pBombArr[i].y][pBombArr[i].x + 1] == '0') {
				Maze[pBombArr[i].y][pBombArr[i].x + 1] = '1';
			}
			// �÷��̾ ��ź�� �¾��� �� ���������� ������.
			if (pPlayer->x == pBombArr[i].x + 1 && pPlayer->y == pBombArr[i].y) {
				pPlayer->x = pStartPost->x;
				pPlayer->y = pStartPost->y;
			}
		}
	}
	// ��ź ���� �ʱ�ȭ
	*pBombCount = 0;
}


int main() {
	// 20X20 �̷θ� �����.
	char strMaze[21][21] = {};

	POINT tPlayerPos;
	POINT tStartPos;
	POINT tEndPos;

	int iBombCount = 0;
	POINT tBombPos[BOMB_MAX];

	// �̷θ� �����Ѵ�.
	SetMaze(strMaze, &tPlayerPos, &tStartPos, &tEndPos);

	while (true) {
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze, &tPlayerPos);

		// �������� �����ߴ��� Ȯ��
		if (tPlayerPos.x == tEndPos.x && tPlayerPos.y == tEndPos.y) {
			cout << "�����߽��ϴ�." << endl;
			break;
		}

		cout << "T: ��ź��ġ / U: ��ź ��Ʈ����" << endl;
		cout << "W: �� / S: �Ʒ� / A: ���� / D: ������ / Q: ����";

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