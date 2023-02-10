// ����ũ�帮��Ʈ

#include <iostream>
#include "List.h"
using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

int OutputMenu() {
	system("cls");
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л��˻�" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ���: ";

	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT) {
		return MM_NONE;
	}
	return iInput;
}

void Search(PLIST pList) {
	system("cls");
	cout << "=================== �л��˻� ===================" << endl;

	cout << "�˻��� �̸��� �Է��ϼ���: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		if (strcmp(strName, pNode->tStudent.strName) == 0) {
			OutputStudent(&pNode->tStudent);
			system("pause");
			return;
		}
		pNode = pNode->pNext;
	}

	cout << "ã�� �л��� �����ϴ�." << endl;
	system("pause");
}

void Delete(PLIST pList) {
	system("cls");
	cout << "=================== �л����� ===================" << endl;

	cout << "������ �̸��� �Է��ϼ���: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(strName, pNode->tStudent.strName) == 0) {
			// ���� ����� ���� ��带 ���´�.
			PNODE pNext = pNode->pNext;

			if (pPrev == NULL) {	// ù ��° ��带 ����ٴ� �ǹ�
				delete pNode;
				pList->pBegin = pNext;

				if (pNext == NULL) {	// ��尡 �ϳ��� ���
					pList->pEnd = NULL;
				}
			}
			else {		// ���� ��尡 ���� ���, ���� ����� ������ ���� ����� ���� ���� �������ش�.
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL) {	// ������ ��带 ����� ���
					pList->pEnd = pPrev;
				}
			}
			cout << strName << " �л� ���� �Ϸ�" << endl;
			pList->iSize--;

			system("pause");
			return;
		}
		pPrev = pNode;
		pNode = pNode->pNext;
	}
	cout << "������ �л��� ã�� �� �����ϴ�." << endl;
	system("pause");
}

int main() {

	LIST tList;

	InitList(&tList);

	while (true) {
		int iMenu = OutputMenu();

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu) {
		case MM_INSERT:
			Push_Back(&tList);
			break;
		case MM_DELETE:
			//Delete(&tList);
			break;
		case MM_SEARCH:
			//Search(&tList);
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		}
	}

	DestroyList(&tList);

	return 0;
}