// ����ü�� �̿��� �л��������α׷�1

#include <iostream>

#define NAME_SIZE		32
#define ADDRESS_SIZE	128
#define PHONE_SIZE		14
#define STUDENT_MAX		10

using namespace std;

struct _tagStudent {
	char strName[NAME_SIZE];
	char strAdress[ADDRESS_SIZE];
	char strPhoneNumber[PHONE_SIZE];
	int iNumber;
	int iKor;
	int iMath;
	int iEng;
	int iTotal;
	float fAvg;
};

enum MENU {
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT
};

int main() {
	
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	int iStudentCount = 0;
	int iStdNumber = 1;

	char strSearchName[NAME_SIZE] = {};

	while (true) {
		system("cls");

		// �޴��� ����Ѵ�.
		cout << "1. �л����" << endl;
		cout << "2. �л�����" << endl;
		cout << "3. �л�Ž��" << endl;
		cout << "4. �л����" << endl;
		cout << "5. ����" << endl;
		cout << "�޴��� �����ϼ���: ";
		
		int iMenu;
		cin >> iMenu;

		// cin�� ���� Ÿ�Կ� ���缭 ���� �Է��ؾ��ϴµ� �ٸ� Ÿ���� ���ڸ� �Է��� ��� ������ �߻��Ѵ�.
		// �׷��� ������ ����ó���� ������ �߻��ߴ����� ���⼭ üũ�Ͽ� ������ �߻��ϸ� cin ������ �������۸� ����ش�.
		// cin ���ο� �Է¹��۰� �ִµ� �Է¹��۴� �Է��� ���� �����س��� �� ���� ������ �־��ִ� ������ �Ѵ�.
		// �� �Է¹��ۿ� \n�� ���������Ƿ� ���۸� ��ȸ�Ͽ� \n�� �����ش�.
		// ����: �ӽ��������
		// ���� ������ üũ�Ѵ�. cin.fail()�� ���� �� �Է� ������ �߻��� ��� true�� ��ȯ�Ѵ�.
		if (cin.fail()) {
			// ���� ���۸� ����ش�.
			cin.clear();

			// �Է� ���ۿ� \n�� ���������Ƿ� �Է¹��۸� �˻��� \n�� �����ش�.
			// cin.ignore(�˻��ϰ����ϴ� ���� ũ��, ã�� ����);
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT) {
			break;
		}

		switch (iMenu) {
		case MENU_INSERT:
			system("cls");
			cout << "============ �л� �߰� ============" << endl;
			// �л� ������ �߰��Ѵ�. �̸�, �ּ�, ��ȭ��ȣ, ������ �Է� �ް� �й�, ����, ����� ������ ���� ������ش�.

			// �� �̻� ����� �� ���� ��� (��� �ִ�ġ) ��� �Ұ�
			if (iStudentCount == STUDENT_MAX) {
				break;
			}
			cout << "�̸�: ";
			cin >> tStudentArr[iStudentCount].strName;

			cout << "�ּ�: ";
			cin.ignore(1024, '\n');
			cin.getline(tStudentArr[iStudentCount].strAdress, ADDRESS_SIZE);

			cout << "��ȭ��ȣ: ";
			cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

			cout << "����: ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "����: ";
			cin >> tStudentArr[iStudentCount].iMath;

			cout << "����: ";
			cin >> tStudentArr[iStudentCount].iEng;

			tStudentArr[iStudentCount].iTotal =
				tStudentArr[iStudentCount].iKor +
				tStudentArr[iStudentCount].iMath +
				tStudentArr[iStudentCount].iEng;

			tStudentArr[iStudentCount].fAvg =
				tStudentArr[iStudentCount].iTotal / 3.f;

			tStudentArr[iStudentCount].iNumber = iStdNumber;

			iStudentCount++;
			iStdNumber++;

			cout << "�л� �߰� �Ϸ�" << endl;
			break;

		case MENU_DELETE:
			system("cls");
			cout << "============ �л� ���� ============" << endl;

			cin.ignore(1024, '\n');
			cout << "������ �̸��� �Է��ϼ���: ";
			cin.getline(strSearchName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					for (int j = i; j < iStudentCount - 1; j++) {
						tStudentArr[i] = tStudentArr[i + 1];
					}
					iStudentCount--;

					cout << "�л� ������ �����߽��ϴ�." << endl;
					break;
				}
			}
			break;

		case MENU_SEARCH:
			system("cls");
			cout << "============ �л� Ž�� ============" << endl;	

			cin.ignore(1024, '\n');
			cout << "Ž���� �̸��� �Է��ϼ���: ";
			cin.getline(strSearchName, NAME_SIZE);
			
			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					cout << "�̸�: " << tStudentArr[i].strName << endl;
					cout << "�ּ�: " << tStudentArr[i].strAdress << endl;
					cout << "��ȭ��ȣ: " << tStudentArr[i].strPhoneNumber << endl;
					cout << "�й�: " << tStudentArr[i].iNumber << endl;
					cout << "����: " << tStudentArr[i].iKor << endl;
					cout << "����: " << tStudentArr[i].iMath << endl;
					cout << "����: " << tStudentArr[i].iEng << endl;
					cout << "����: " << tStudentArr[i].iTotal << endl;
					cout << "���: " << tStudentArr[i].fAvg << endl << endl;
					break;
				}
			}
			break;

		case MENU_OUTPUT:
			system("cls");
			cout << "============ �л� ��� ============" << endl;

			for (int i = 0; i < iStudentCount; i++) {
				cout << "�̸�: " << tStudentArr[i].strName << endl;
				cout << "�ּ�: " << tStudentArr[i].strAdress << endl;
				cout << "��ȭ��ȣ: " << tStudentArr[i].strPhoneNumber << endl;
				cout << "�й�: " << tStudentArr[i].iNumber << endl;
				cout << "����: " << tStudentArr[i].iKor << endl;
				cout << "����: " << tStudentArr[i].iMath << endl;
				cout << "����: " << tStudentArr[i].iEng << endl;
				cout << "����: " << tStudentArr[i].iTotal << endl;
				cout << "���: " << tStudentArr[i].fAvg << endl << endl;
			}

			break;

		default:
			cout << "�޴��� �߸� �����߽��ϴ�." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}