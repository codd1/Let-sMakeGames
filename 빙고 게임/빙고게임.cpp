/*
	�������
	����: ���ں�������� ������.
	1~25������ ���ڰ� �ְ� �� ���ڸ� ���� ��� 5x5�� ����Ѵ�.
	�÷��̾�� ���ڸ� �Է¹޴´�. 1~25 ������ ���ڸ� �Է¹޾ƾ��Ѵ�.
	0�� �Է��ϸ� ������ �����Ѵ�.

	���ڸ� �Է¹޾����� ���ڸ�� �� �Է¹��� ���ڸ� ã�Ƽ� *�� ������ش�.
	���ڸ� *�� ���� �Ŀ� ���� �� ���� üũ�Ѵ�. 5x5�̱� ������ ���� 5��, ���� 5��, �밢�� 2���� ���� �� �ִ�.
	�������� �� �������� üũ�ؼ� ȭ�鿡 �����ش�.
	5�� �̻��� ��� ������ �����Ѵ�.
*/

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

int main() {
	srand((unsigned int)time(0));

	// �迭�� 1~25 �� ����
	int iNumber[25] = {};
	int iAINumber[25] = {};

	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
		iAINumber[i] = i + 1;
	}

	// �迭 �� �����ϰ� ����
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		// �÷��̾� �迭 ����
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;

		// AI �迭 ����
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iAINumber[idx1];
		iAINumber[idx1] = iAINumber[idx2];
		iAINumber[idx2] = temp;

	}

	int bingo = 0, AIbingo = 0;		// �� ���� ��
	int wLine, hLine, dLine1, dLine2;		// �÷��̾��� ���� ��, ���� ��, �밢����2��
	int wAILine, hAILine, dAILine1, dAILine2;	// AI�� ~~

	int iAIMode;

	int iNoneSelect[25] = {};		// EASY ��� AI�� ������ ���� ���
	int iNoneSelectCount = 0;

	// AI ���̵��� �����Ѵ�.
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

	while (true) {
		system("cls");

		// �÷��̾� 5X5 ������ ���
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


		// AI 5X5 ������ ���
		cout << "============== AI ==============" << endl;
		// AI Mode ���
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


		// ���� �ʱ�ȭ
		bingo = wLine = hLine = dLine1 = dLine2 = 0;
		AIbingo = wAILine = hAILine = dAILine1 = dAILine2 = 0;

		// �÷��̾ ���ڸ� �Է��ϰ�, �Է� ���� ���� ��ġ�� �� ���(INT_MAX) �� ����
		int input;
		cout << "���ڸ� �Է����ּ���(1 ~ 25): ";
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

		// AI�� ���ڸ� �����Ѵ�. AI�� �����ϴ� ���� AI��忡 ���� �޶�����.
		switch (iAIMode) {
			/*
				AI Easy ���� ���� AI�� ���� ��� ��
				*�� �ٲ��� ���� ���� ����� ���� �� ��� �� �ϳ��� �����ϰ� �Ѵ�. (�����ϰ�)
			*/
		case AM_EASY:
			// ���ݱ��� ���� �ȵ� ���� ����� ������ش�.
			iNoneSelectCount = 0;
			for (int i = 0; i < 25; i++) {
				if (iAINumber[i] != INT_MAX) {
					iNoneSelect[iNoneSelectCount] = iAINumber[i];
					iNoneSelectCount++;
				}
			}
			// ���� ���� �� AI�� �����ϰ� �����Ѵ�.
			input = iNoneSelect[rand() % iNoneSelectCount];
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
					if (iAINumber[i * 5 + j] == INT_MAX) {
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
					if (iAINumber[j * 5 + i] == INT_MAX) {
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
				if (iAINumber[i] == INT_MAX) {
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
				if (iAINumber[i] == INT_MAX) {
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
					if (iAINumber[iLine * 5 + i] != INT_MAX) {
						input = iAINumber[iLine * 5 + i];
						break;
					}
				}
			}
			else if (iLine <= LN_H5) {	// ���ɼ��� ���� ���� ���� �� �� �ϳ����
				for (int i = 0; i < 5; i++) {
					// LN_H1 ~ LN_H5�� 5~9 �̹Ƿ� iLine-5�� �Ѵ�. �׷��� 0~4�� ��.
					if (iAINumber[i * 5 + (iLine - 5)] != INT_MAX) {
						input = iAINumber[i * 5 + (iLine - 5)];
						break;
					}
				}
			}
			else if (iLine == LN_LT) {	// ���ɼ��� ���� ���� �� �밢���̶��
				for (int i = 0; i < 25; i += 6) {
					if (iAINumber[i] != INT_MAX) {
						input = iAINumber[i];
						break;
					}
				}
			}
			else if (iLine == LN_RT) {	// ���ɼ��� ���� ���� �� �밢���̶��
				for (int i = 4; i <= 20; i += 4) {
					if (iAINumber[i] != INT_MAX) {
						input = iAINumber[i];
						break;
					}
				}
			}
			break;
		}

		// AI�� ������ ���� ��ġ�� �� ���(INT_MAX) �� ����
		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				iNumber[i] = INT_MAX;
			}
			if (input == iAINumber[i]) {
				iAINumber[i] = INT_MAX;
			}
		}



		// ���� Ȯ�� - �÷��̾�

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				// ���� �� Ȯ��
				if (iNumber[i * 5 + j] == INT_MAX) {
					wLine++;
				}
				// ���� �� Ȯ��
				if (iNumber[j * 5 + i] == INT_MAX) {
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
		// �밢�� ���� Ȯ��
		for (int i = 0; i < 25; i++) {
			// �� �밢�� Ȯ��
			if ((i != 0) && (i % 4 == 0) && (i < 24) && iNumber[i] == INT_MAX) {
				dLine1++;
			}
			// �� �밢�� Ȯ��
			if ((i % 6 == 0) && iNumber[i] == INT_MAX) {
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


		// ���� Ȯ�� - AI

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				// ���� �� Ȯ��
				if (iAINumber[i * 5 + j] == INT_MAX) {
					wAILine++;
				}
				// ���� �� Ȯ��
				if (iAINumber[j * 5 + i] == INT_MAX) {
					hAILine++;
				}
			}
			if (wAILine == 5) {		// ���� �� ���� Ȯ��
				AIbingo++;
			}
			if (hAILine == 5) {		// ���� �� ���� Ȯ��
				AIbingo++;
			}
			wAILine = 0;
			hAILine = 0;
		}
		// �밢�� ���� Ȯ��
		for (int i = 0; i < 25; i++) {
			// �� �밢�� Ȯ��
			if ((i != 0) && (i % 4 == 0) && (i < 24) && iAINumber[i] == INT_MAX) {
				dAILine1++;
			}
			// �� �밢�� Ȯ��
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



		// ���� ���� Ȯ�� (���� 5�� �� ����)
		if (bingo >= 5) {
			cout << endl << "Player �¸�" << endl;
			break;
		}
		else if (AIbingo >= 5) {
			cout << endl << "AI �¸�" << endl;
			break;
		}

	}

	cout << "���� ������ ����Ǿ����ϴ�." << endl;

	return 0;
}