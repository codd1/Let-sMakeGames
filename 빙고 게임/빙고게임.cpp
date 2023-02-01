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

int main() {
	srand((unsigned int)time(0));

	// �迭�� 1~25 �� ����
	int iNumber[25] = {};
	for (int i = 0; i < 25; i++) {
		iNumber[i] = i + 1;
	}

	// �迭 �� �����ϰ� ����
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 25;
		idx2 = rand() % 25;

		temp = iNumber[idx1];
		iNumber[idx1] = iNumber[idx2];
		iNumber[idx2] = temp;
	}

	int bingo = 0;	// �� ���� ��
	int wLine = 0;	// ���� �� (5��� ���� �� �� �ϼ�)
	int hLine = 0;	// ���� �� (5��� ���� �� �� �ϼ�)
	int dLine1 = 0;	// �밢�� �� (5��� �밢�� �� �� �ϼ�)
	int dLine2 = 0;

	while (true) {
		system("cls");

		// ������ ���
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

		// �÷��̾�� �Է� �ް� �Է� ���� ���� �� ���(INT_MAX) �� ����
		int input;
		cin >> input;

		for (int i = 0; i < 25; i++) {
			if (input == iNumber[i]) {
				iNumber[i] = INT_MAX;
			}
		}


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
				// �밢�� �� �� �� ���� Ȯ��
				if ((i * 5 + j) != 0 && ((i * 5 + j) % 4) == 0 && iNumber[i * 5 + j] == INT_MAX) {
					dLine1++;
				}
				// �밢�� �� �� �� ���� Ȯ��
				if (((i * 5 + j) % 6) == 0 && iNumber[i * 5 + j] == INT_MAX) {
					dLine2++;
				}
			}
			if (wLine == 5) {		// ���� �� ���� Ȯ��
				bingo++;
			}
			if (hLine == 5) {		// ���� �� ���� Ȯ��
				bingo++;
			}
			hLine = 0;
			wLine = 0;
		}

		// �밢�� ���� Ȯ��
		if (dLine1 == 5) {
			bingo++;
		}
		if (dLine2 == 5) {
			bingo++;
		}

		// ���� ���� Ȯ�� (���� 5�� �� ����)
		if (bingo == 5) {
			cout << "Clear!!!" << endl;
			break;
		}

		// ���� �ʱ�ȭ
		bingo = 0;
		dLine1 = 0;
		dLine2 = 0;
	}

	cout << "���� ������ ����Ǿ����ϴ�." << endl;

	return 0;
}