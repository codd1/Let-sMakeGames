#include "List.h"

// const 포인터이기 때문에 가리키는 대상의 값을 변경할 수 없다.
void OutputStudent(const PSTUDENT pStudnet) {
	cout << "이름: " << pStudnet->strName << "\t학번: " << pStudnet->iNumber << endl;
	cout << "국어: " << pStudnet->iKor << "\t영어: " << pStudnet->iEng << "\t수학: " << pStudnet->iMath << endl;
	cout << "총점: " << pStudnet->iTotal << "\t평균: " << pStudnet->fAvg << endl << endl;
}

void InitList(PLIST pList) {
	pList->pBegin = new NODE;
	pList->pEnd = new NODE;

	// 시작 노드의 다음 노드는 마지막 노드이다.
	pList->pBegin->pNext = pList->pEnd;

	// 마지막 노드의 이전 노드는 시작 노드이다.
	pList->pEnd->pPrev = pList->pBegin;

	// 마지막 노드의 다음 노드는 없으므로 NULL
	pList->pBegin->pPrev = NULL;

	// 시작 노드의 이전 노드는 없으므로 NULL
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
	cout << "=================== 학생추가 ===================" << endl;

	STUDENT tStudent = {};

	cout << "이름: ";
	InputString(tStudent.strName, NAME_SIZE);
	cout << "학번: ";
	tStudent.iNumber = InputInt();
	cout << "국어: ";
	tStudent.iKor = InputInt();
	cout << "영어: ";
	tStudent.iEng = InputInt();
	cout << "수학: ";
	tStudent.iMath = InputInt();

	tStudent.iTotal = tStudent.iKor + tStudent.iEng + tStudent.iMath;
	tStudent.fAvg = tStudent.iTotal / 3.f;

	PNODE pNode = new NODE;

	pNode->tStudent = tStudent;

	// 새로 추가되는 노드(pNode)는 End노드의 이전 노드와 End 노드 사이에 추가해야한다.
	// 그래서 pEnd의 이전 노드를 구해놓는다.
	PNODE pPrev = pList->pEnd->pPrev;

	// pEnd 노드 이전 노드의 다음으로 새로 추가할 노드를 지정한다.
	pPrev->pNext = pNode;
	// 추가할 노드의 이전 노드로 End의 이전 노드를 지정한다.
	pNode->pPrev = pPrev;

	// 새로 추가할 노드의 다음 노드를 pEnd에 연결한다.
	pNode->pNext = pList->pEnd;

	// pEnd 노드의 이전 노드로 새로 추가할 노드를 지정한다.
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
		cout << "=================== 학생출력 ===================" << endl;
		cout << "1. 정방향 출력" << endl;
		cout << "2. 역방향 출력" << endl;
		cout << "메뉴를 선택하세요: ";

		iMenu = InputInt();

		if (iMenu > OT_NONE && iMenu <= OT_INVERSE) {
			break;
		}
	}
	
	PNODE pNode = NULL;

	switch (iMenu)
	{
	case OT_OUTPUT:
		// 추가되는 노드들은 begin과 end 사이에 배치된다.
		// 그러므로 begin의 다음 노드를 얻어온다.
		pNode = pList->pBegin->pNext;

		// 노드가 End노드와 같아지면 더이상 출력할 노드가 없으므로 반복 종료
		while (pNode != pList->pEnd) {
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pNext;
		}
		break;
	case OT_INVERSE:
		// 역방향으로 출력할 때는 end의 이전 노드를 얻어오고 계속 이전노드로 진행한다.
		pNode = pList->pEnd->pPrev;

		// 역방향으로 들어가기 때문에 begin과 같아질 경우 반복 종료
		while (pNode != pList->pBegin) {
			OutputStudent(&pNode->tStudent);
			pNode = pNode->pPrev;
		}
		break;
	}
	cout << "학생 수:" << pList->iSize << endl;
	system("pause");
}