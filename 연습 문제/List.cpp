#include "List.h"

// const �������̱� ������ ����Ű�� ����� ���� ������ �� ����.
void OutputStudent(const PSTUDENT pStudnet) {
	cout << "�̸�: " << pStudnet->strName << "\t�й�: " << pStudnet->iNumber << endl;
	cout << "����: " << pStudnet->iKor << "\t����: " << pStudnet->iEng << "\t����: " << pStudnet->iMath << endl;
	cout << "����: " << pStudnet->iTotal << "\t���: " << pStudnet->fAvg << endl << endl;
}

void InitList(PLIST pList) {
	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	// ���� ����� ���� ���� ������ ����̴�.
	pList->pBegin->pNext = pList->pEnd;

	// ������ ����� ���� ���� ���� ����̴�.
	pList->pEnd->pPrev = pList->pBegin;

	// ������ ����� ���� ���� �����Ƿ� NULL
	pList->pBegin->pPrev = NULL;

	// ���� ����� ���� ���� �����Ƿ� NULL
	pList->pEnd->pNext = NULL;

	pList->iSize = 0;
}

void DestroyList(PLIST pList) {
	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		PNODE pNext = pNode->pNext;
		delete pNode;
		pNode = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

void Push_Back(PLIST pList)
{
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

	PNODE pNode = new NODE;

	pNode->tStudent = tStudent;

	// ���� �߰��Ǵ� ���(pNode)�� End����� ���� ���� End ��� ���̿� �߰��ؾ��Ѵ�.
	// �׷��� pEnd�� ���� ��带 ���س��´�.
	PNODE pPrev = pList->pEnd->pPrev;

	// pEnd ��� ���� ����� �������� ���� �߰��� ��带 �����Ѵ�.
	pPrev->pNext = pNode;
	// �߰��� ����� ���� ���� End�� ���� ��带 �����Ѵ�.
	pNode->pPrev = pPrev;

	// ���� �߰��� ����� ���� ��带 pEnd�� �����Ѵ�.
	pNode->pNext = pList->pEnd;

	// pEnd ����� ���� ���� ���� �߰��� ��带 �����Ѵ�.
	pList->pEnd->pPrev = pNode;

	pList->iSize++;
}

void Push_Front(PLIST pList)
{

}

void Output(PLIST pList) {
	int iMenu;
	while (true) {
		system("cls");
		cout << "=================== �л���� ===================" << endl;
		cout << "1. ������ ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "�޴��� �����ϼ���: ";

		iMenu = InputInt();

		if (iMenu > OT_NONE && iMenu <= OT_INVERSE) {
			break;
		}
	}
	
	PNODE pNode = NULL;

	switch (iMenu)
	{
	case OT_OUTPUT:
		// �߰��Ǵ� ������ begin�� end ���̿� ��ġ�ȴ�.
		// �׷��Ƿ� begin�� ���� ��带 ���´�.
		pNode = pList->pBegin->pNext;

		// ��尡 End���� �������� ���̻� ����� ��尡 �����Ƿ� �ݺ� ����
		while (pNode != pList->pEnd) {
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		// ���������� ����� ���� end�� ���� ��带 ������ ��� �������� �����Ѵ�.
		pNode = pList->pEnd->pPrev;

		// ���������� ���� ������ begin�� ������ ��� �ݺ� ����
		while (pNode != pList->pBegin) {
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}
	cout << "�л� ��:" << pList->iSize << endl;
	system("pause");
}