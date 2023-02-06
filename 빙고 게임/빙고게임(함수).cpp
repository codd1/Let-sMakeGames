// ��������� �Լ��� ��ȯ

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

// �Լ��� ����� ���� �κ����� ���� �� �ִ�.
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

	// �迭�� 1~25 �� ����
	int iNumber[25] = {};
	int iAINumber[25] = {};

	SetNumber(iNumber);
	SetNumber(iAINumber);

	// �迭 �� �����ϰ� ����
	Shuffle(iNumber);
	Shuffle(iAINumber);

	int iBingo = 0, iAIbingo = 0;		// �� ���� ��

	// AI ���̵��� �����Ѵ�.
	AI_MODE eAIMode = SelectAIMode();

	while (true) {
		system("cls");

		// �÷��̾� 5X5 ������ ���
		cout << "============= Player =============" << endl;
		OutputNumber(iNumber, iBingo);

		// AI 5X5 ������ ���
		cout << "============== AI ==============" << endl;
		// AI Mode ���
		switch (eAIMode) {
		case AM_EASY:
			cout << "AI Mode: EASY" << endl;
			break;
		case AM_HARD:
			cout << "AI Mode: Hard" << endl;
			break;
		}
		OutputNumber(iAINumber, iAIbingo);


		// ���� �ʱ�ȭ
		iBingo = iAIbingo = 0;

		// �÷��̾ ���ڸ� �Է��ϰ�, �Է� ���� ���� ��ġ�� �� ���(INT_MAX) �� ����
		int input;
		cout << "���ڸ� �Է����ּ���(1 ~ 25): ";
		cin >> input;

		if (input == 0) {
			break;
		}
		StoreStarValue(iNumber, iAINumber, input);

		// AI�� ���ڸ� �����Ѵ�. AI�� �����ϴ� ���� AI��忡 ���� �޶�����.
		input = SelectAINumber(iAINumber, eAIMode);
		// AI�� ������ ���� ��ġ�� �� ���(INT_MAX) �� ����
		StoreStarValue(iNumber, iAINumber, input);


		// ���� Ȯ�� - �÷��̾�
		iBingo = BingoLineCheckWH(iNumber, iBingo);
		iBingo = BingoLineCheckD(iNumber, iBingo);
		// ���� Ȯ�� - AI
		iAIbingo = BingoLineCheckWH(iAINumber, iAIbingo);
		iAIbingo = BingoLineCheckD(iAINumber, iAIbingo);


		// ���� ���� Ȯ�� (���� 5�� �� ����)
		if (iBingo >= 5) {
			cout << endl << "Player �¸�" << endl;
			break;
		}
		else if (iAIbingo >= 5) {
			cout << endl << "AI �¸�" << endl;
			break;
		}
	}

	cout << "���� ������ ����Ǿ����ϴ�." << endl;

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
		// �÷��̾� �迭 ����
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
		cout << "AI ��带 �����ϼ���: ";

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
			// ���� �� Ȯ��
			if (pArray[i * 5 + j] == INT_MAX) {
				wLine++;
			}
			// ���� �� Ȯ��
			if (pArray[j * 5 + i] == INT_MAX) {
				hLine++;
			}
		}
		if (wLine == 5) {		// ���� �� ���� Ȯ��
			//cout << "���� �� ����" << endl;
			bingo++;
		}
		if (hLine == 5) {		// ���� �� ���� Ȯ��
			//cout << "���� �� ����" << endl;
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

	// �밢�� ���� Ȯ��
	for (int i = 0; i < 25; i++) {
		// �� �밢�� Ȯ��
		if ((i != 0) && (i % 4 == 0) && (i < 24) && pArray[i] == INT_MAX) {
			dLine1++;
		}
		// �� �밢�� Ȯ��
		if ((i % 6 == 0) && pArray[i] == INT_MAX) {
			dLine2++;
		}
	}
	if (dLine1 == 5) {
		//cout << "�� �밢�� ����" << endl;
		bingo++;
	}
	if (dLine2 == 5) {
		//cout << "�� �밢�� ����" << endl;
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
	int iNoneSelect[25] = {};		// EASY ��� AI�� ������ ���� ���
	int iNoneSelectCount = 0;
	int iAISelectNum = 0;

	// AI�� ���ڸ� �����Ѵ�. AI�� �����ϴ� ���� AI��忡 ���� �޶�����.
	switch (eMode) {
		/*
			AI Easy ���� ���� AI�� ���� ��� ��
			*�� �ٲ��� ���� ���� ����� ���� �� ��� �� �ϳ��� �����ϰ� �Ѵ�. (�����ϰ�)
		*/
	case AM_EASY:
		// ���ݱ��� ���� �ȵ� ���� ����� ������ش�.
		iNoneSelectCount = 0;
		for (int i = 0; i < 25; i++) {
			if (pArray[i] != INT_MAX) {
				iNoneSelect[iNoneSelectCount] = pArray[i];
				iNoneSelectCount++;
			}
		}
		// ���� ���� �� AI�� �����ϰ� �����Ѵ�.
		iAISelectNum = iNoneSelect[rand() % iNoneSelectCount];
		break;
	case AM_HARD:
		/*
			AI Hard ���� ���� ���� �� ������ �ϼ� ���ɼ��� ���� ���� ���� ã�Ƽ�
			�� �ٿ� �ִ� ���� �� �ϳ��� *�� ������ش�.
			���� ���� ���� ��������� ������ ã�Ƽ� �� ���ο� �ִ� ���ڸ� �����Ѵ�.
		*/
		int iLine = 0;
		int iStarCount = 0;
		int iSaveMaxCount = 0;		// *�� ���� ���� ���� *�� ����

		// ���� ���ο��� ���� *�� ���� ������ ã�´�.
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
		// ���� ���ΰ� ���� ���ε��� ���� ���� ���� ���� ������ ���Ѵ�.
		for (int i = 0; i < 5; i++) {
			iStarCount = 0;
			for (int j = 0; j < 5; j++) {
				if (pArray[j * 5 + i] == INT_MAX) {
					iStarCount++;
				}
			}
			if (iStarCount < 5 && iSaveMaxCount < iStarCount) {
				iLine = i + 5;		// ���� ������ 5 ~ 9�̹Ƿ� +5
				iSaveMaxCount = iStarCount;
			}
		}

		// �� �밢�� üũ
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

		// �� �밢�� üũ
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

		// ��� ������ ���������� iLine�� ���ɼ��� ���� ���� �� ��ȣ�� ����ȴ�.
		// AI�� �� �ٿ� �ִ� *�� �ƴ� ���� �� �ϳ��� ����
		if (iLine <= LN_W5) {		// ���ɼ��� ���� ���� ���� �� �� �ϳ����
			for (int i = 0; i < 5; i++) {
				if (pArray[iLine * 5 + i] != INT_MAX) {
					iAISelectNum = pArray[iLine * 5 + i];
					break;
				}
			}
		}
		else if (iLine <= LN_H5) {	// ���ɼ��� ���� ���� ���� �� �� �ϳ����
			for (int i = 0; i < 5; i++) {
				// LN_H1 ~ LN_H5�� 5~9 �̹Ƿ� iLine-5�� �Ѵ�. �׷��� 0~4�� ��.
				if (pArray[i * 5 + (iLine - 5)] != INT_MAX) {
					iAISelectNum = pArray[i * 5 + (iLine - 5)];
					break;
				}
			}
		}
		else if (iLine == LN_LT) {	// ���ɼ��� ���� ���� �� �밢���̶��
			for (int i = 0; i < 25; i += 6) {
				if (pArray[i] != INT_MAX) {
					iAISelectNum = pArray[i];
					break;
				}
			}
		}
		else if (iLine == LN_RT) {	// ���ɼ��� ���� ���� �� �밢���̶��
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