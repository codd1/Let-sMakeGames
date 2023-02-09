// 싱글 링크드리스트

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
	링크드리스트: 자료구조의 한 종류이다. 자료구조란 데이터를 관리하는 방법을 말한다.
	링크드리스트는 데이터 목록을 연결시켜서 접근할 수 있는 구조를 제공한다.
	링크드리스트는 데이터를 저장하기 위한 노드라는 것이 존재한다.
	각 노드의 특징은 다음 노드를 알 수 있는 것이다. (다음 노드의 메모리 주소를 저장)
	리스트는 배열처럼 특정 요소에 바로 접근이 불가능하다. 무조건 앞에서부터 차례대로 타고 들어가야한다.
	노드를 새로 추가할 때는 노드를 생성하고 마지막 노드에 연결만 해주면 되기 때문에 개수의 제한이 없다.

	배열: 특정 요소에 바로 접근 가능 / 갯수의 제한이 있다.
	링크드리스트: 처음부터 차례로 접근 가능 / 갯수의 제한이 없다.
*/

// 리스트 노드를 만든다.
typedef struct _tagNode {
	STUDENT tStudent;
	_tagNode* pNext;
}NODE, * PNODE;

// 리스트 구조체를 만든다.
typedef struct _tagList {
	PNODE pBegin;
	PNODE pEnd;
	int iSize;
}LIST, * PLIST;

void InitList(PLIST pList) {
	// 포인터는 가급적이면 초기화할 때 NULL(0)로 초기화해두고 쓰는 것이 좋다.
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
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생탐색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요: ";

	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT) {
		return MM_NONE;
	}
	return iInput;
}

void Insert(PLIST pList) {
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

	// 추가할 리스트 노드를 생성한다.
	PNODE pNode = new NODE;

	// 현재 추가하는 노드는 가장 마지막에 추가되기 때문에 다음 노드가 존재하지 않는다.
	// 그렇기 때문에 다음 노드는 NULL로 초기화하고 정보는 위에서 입력받은 학생정보를 준다.
	pNode->pNext = NULL;
	pNode->tStudent = tStudent;

	// 리스트가 비어있을 경우
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

// const 포인터이기 때문에 가리키는 대상의 값을 변경할 수 없다.
void OutputStudent(const PSTUDENT pStudnet) {
	cout << "이름: " << pStudnet->strName << "\t학번: " << pStudnet->iNumber << endl;
	cout << "국어: " << pStudnet->iKor << "\t영어: " << pStudnet->iEng << "\t수학: " << pStudnet->iMath << endl;
	cout << "총점: " << pStudnet->iTotal << "\t평균: " << pStudnet->fAvg << endl << endl;
}

void Output(PLIST pList) {
	system("cls");
	cout << "=================== 학생출력 ===================" << endl;

	PNODE pNode = pList->pBegin;

	while (pNode != NULL) {
		OutputStudent(&pNode->tStudent);
		pNode = pNode->pNext;
	}
	cout << "학생 수: " << pList->iSize << endl;

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