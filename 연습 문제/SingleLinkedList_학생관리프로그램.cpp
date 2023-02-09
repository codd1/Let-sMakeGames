// �̱� ��ũ�帮��Ʈ

#include <iostream>

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_INSERT,
	MM_DELETE,
	MM_SEARCH,
	MM_OUTPUT,
	MM_EXIT
};

#define NAME_SIZE 32

typedef struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
}STUDENT, * PSTUDENT;

/*
	��ũ�帮��Ʈ: �ڷᱸ���� �� �����̴�. �ڷᱸ���� �����͸� �����ϴ� ����� ���Ѵ�.
	��ũ�帮��Ʈ�� ������ ����� ������Ѽ� ������ �� �ִ� ������ �����Ѵ�.
	��ũ�帮��Ʈ�� �����͸� �����ϱ� ���� ����� ���� �����Ѵ�.
	�� ����� Ư¡�� ���� ��带 �� �� �ִ� ���̴�. (���� ����� �޸� �ּҸ� ����)
	����Ʈ�� �迭ó�� Ư�� ��ҿ� �ٷ� ������ �Ұ����ϴ�. ������ �տ������� ���ʴ�� Ÿ�� �����Ѵ�.
	��带 ���� �߰��� ���� ��带 �����ϰ� ������ ��忡 ���Ḹ ���ָ� �Ǳ� ������ ������ ������ ����.

	�迭: Ư�� ��ҿ� �ٷ� ���� ���� / ������ ������ �ִ�.
	��ũ�帮��Ʈ: ó������ ���ʷ� ���� ���� / ������ ������ ����.
*/

// ����Ʈ ��带 �����.
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, * PNODE;

// ����Ʈ ����ü�� �����.
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, * PLIST;

void InitList(PLIST pList) {
	// �����ʹ� �������̸� �ʱ�ȭ�� �� NULL(0)�� �ʱ�ȭ�صΰ� ���� ���� ����.
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;
	}
	return iInput;
}

void InputString(char* pString, int iSize) {
	cin.clear();
	cin.ignore(1024, '\n');

	cin.getline(pString, iSize - 1);
}

int OutputMenu() {
	system("cls");
	cout << "1. �л��߰�" << endl;
	cout << "2. �л�����" << endl;
	cout << "3. �л�Ž��" << endl;
	cout << "4. �л����" << endl;
	cout << "5. ����" << endl;
	cout << "�޴��� �����ϼ���: ";

	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT) {
		return MM_NONE;
	}
	return iInput;
}

void Insert(PLIST pList) {
	system("cls");
	cout << "=================== �л��߰� ===================" << endl;

	STUDENT tStudent = {};

	cout << "�̸�: ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "�й�: ";
	tStudent.iNumber = InputInt();
	cout << "����: ";
	tStudent.iKor = InputInt();
	cout << "����: ";
	tStudent.iEng = InputInt();
	cout << "����: ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	// �߰��� ����Ʈ ��带 �����Ѵ�.
	PNODE pNode = new NODE;

	// ���� �߰��ϴ� ���� ���� �������� �߰��Ǳ� ������ ���� ��尡 �������� �ʴ´�.
	// �׷��� ������ ���� ���� NULL�� �ʱ�ȭ�ϰ� ������ ������ �Է¹��� �л������� �ش�.
	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	// ����Ʈ�� ������� ���
	if (pList->pBegin == NULL) {
		pList->pBegin = pNode;
	}
	else {
		pList->pEnd->pNext = pNode;
	}
	pList->pEnd = pNode;
}

void ClearList(PLIST pList) {
	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;
}

// const �������̱� ������ ����Ű�� ����� ���� ������ �� ����.
void OutputStudent(const PSTUDENT pStudnet) {
	cout << "�̸�: " << pStudnet->strName << "\t�й�: " << pStudnet->iNumber << endl;
	cout << "����: " << pStudnet->iKor << "\t����: " << pStudnet->iEng << "\t����: " << pStudnet->iMath << endl;
	cout << "����: " << pStudnet->iTotal << "\t���: " << pStudnet->fAvg << endl << endl;
}

void Output(PLIST pList) {
	system("cls");
	cout << "=================== �л���� ===================" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}
	cout << "�л� ��: " << pList->iSize << endl;

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
			Insert(&tList);
			tList.iSize++;
			break;
		case MM_DELETE:
			break;
		case MM_SEARCH:
			break;
		case MM_OUTPUT:
			Output(&tList);
			break;
		}
	}

	ClearList(&tList);

	return 0;
}