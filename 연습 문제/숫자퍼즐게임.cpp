// ���� ���� ����

#include <iostream>
#include <time.h>

// console input output �������.
// �ܼ�â���� ������ϴ� ��ɵ��� �������ش�.
#include <conio.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iNumber[25] = {};
	
	for (int i = 0; i < 24; i++) {
		iNumber[i] = i + 1;
	}

	// ���� ������ ĭ�� �������� ����д�.
	// ������ �ǹ��ϴ� ������ Ư���� ���� INT_MAX��� ���� ����� ���̴�.

	iNumber[24] = INT_MAX;

	// ���� �ִ� ��ġ�� ������ ������ ������ش�.
	int iStarIndex = 24;		// �ε��� ��ȣ

	// ������ ������ �����ϰ� 1 ~ 24 ������ ���ڸ� �����ش�.
	// �� �ε����� 0 ~ 23�� �ε��������� �����ش�.
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
		// ������ ���߾����� Ȯ���Ѵ�.
		for (int i = 0; i < 24; i++) {
			if (iNumber[i] != i + 1) {
				bWin = false;
				break;
			}
		}
		if (bWin == true) {
			cout << "����!!!" << endl;
			break;
		}

		cout << "W: �� / S: �Ʒ� / A: ���� / D: ������ / Q: ����" << endl;

		// _getch() �Լ��� ���� 1���� �Է¹޴� �Լ��̴�.
		// �� �Լ��� Enter�� ġ�� �ʴ��� ���ڸ� ������ ���� �� ���ڸ� ��ȯ�ϰ� ����
		char cInput = _getch();

		if (cInput == 'q' || cInput == 'Q') {
			break;
		}

		switch (cInput) {
		case 'w':
		case 'W':
			if (iStarIndex > 4) {	// �� �� ���� �ƴ� ���
				// �� ĭ�� �ε����� ��ȯ
				iNumber[iStarIndex] = iNumber[iStarIndex - 5];
				iNumber[iStarIndex - 5] = INT_MAX;
				iStarIndex -= 5;
			}
			break;
		case 's':
		case 'S':
			if (iStarIndex < 20) {	// �� �Ʒ� ���� �ƴ� ���
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
	
	cout << "������ �����մϴ�." << endl;


	return 0;
}