// �̷� ����

#include <iostream>
#include <conio.h>

using namespace std;

/*
	0: ��
	1: ��
	2: ������
	3: ������
*/
void SetMaze(char Maze[21][21]) {
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
	strcpy_s(Maze[18], "00001100011111011113");
	strcpy_s(Maze[19], "00000001110001110000");
}

void Output(char Maze[21][21]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			if (Maze[i][j] == '0') {
				cout << "��";
			}
			else if (Maze[i][j] == '1') {
				cout << "  ";
			}
			else if (Maze[i][j] == '2') {
				cout << "��";
			}
			else if (Maze[i][j] == '3') {
				cout << "��";
			}
		}
		cout << endl;
	}
}

int main() {
	// 20X20 �̷θ� �����.
	char strMaze[21][21] = {};

	// �̷θ� �����Ѵ�.
	SetMaze(strMaze);

	while (true) {
		system("cls");
		// �̷θ� ����Ѵ�.
		Output(strMaze);
		cout << "W: �� / S: �Ʒ� / A: ���� / D: ������ / Q: ���� ";
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}
	}
	
	return 0;
}