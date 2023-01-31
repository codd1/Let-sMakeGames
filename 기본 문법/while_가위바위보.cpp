// while���� ���������� ����

#include <iostream>
#include <time.h>

using namespace std;

enum SRP {
	SRP_S = 1,		// ����
	SRP_R,			// ����
	SRP_P,			// ��
	SRP_END
};

int main() {
	/*
		�ݺ��� : Ư�� �۾��� �ݺ��ؼ� �������ִ� ����̴�.
		����: for, while, do while 3������ �����Ѵ�.
	*/

	int iNumber = 0;
	while (iNumber < 10) {
		cout << iNumber << endl;
		++iNumber;

		if (iNumber == 4)
			break;
	}

	// ȭ���� ������ �����ش�.
	system("cls");

	// ���� ���̺� ����
	srand((unsigned int)time(0));

	int iPlayer, iAI;

	while (true) {
		cout << "1. ����" << endl;
		cout << "2. ����" << endl;
		cout << "3. ��" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ���: ";
		cin >> iPlayer;

		if (iPlayer < SRP_S || iPlayer > SRP_END) {
			cout << "�߸��� ���� �Է��Ͽ����ϴ�." << endl;
			//�Ͻ�����
			system("pause");
			// continue: �ݺ����� ���������� �̵������ִ� ����̴�.
			continue;
		}
		else if (iPlayer == SRP_END) {
			break;
		}
		
		// ���� ������ �Ѵ�.
		iAI = rand() % 3 + SRP_S;
		
		switch (iAI) {
		case SRP_S:
			cout << "AI: ����" << endl;
			break;
		case SRP_R:
			cout << "AI: ����" << endl;
			break;
		case SRP_P:
			cout << "AI: ��" << endl;
			break;
		}

		int iWin = iPlayer - iAI;

		if (iWin == 1 || iWin == -2) {
			cout << "Player �¸�" << endl;
		}
		else if (iWin == 0) {
			cout << "���" << endl;
		}
		else {
			cout << "AI �¸�" << endl;
		}

		system("pause");
	}

	return 0;
}