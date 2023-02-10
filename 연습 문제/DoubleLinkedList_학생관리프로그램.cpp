// 더블링크드리스트

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
	cout << "1. 학생추가" << endl;
	cout << "2. 학생삭제" << endl;
	cout << "3. 학생검색" << endl;
	cout << "4. 학생출력" << endl;
	cout << "5. 종료" << endl;
	cout << "메뉴를 선택하세요: ";

	int iInput = InputInt();

	if (iInput <= MM_NONE || iInput > MM_EXIT) {
		return MM_NONE;
	}
	return iInput;
}

void Search(PLIST pList) {
	system("cls");
	cout << "=================== 학생검색 ===================" << endl;

	cout << "검색할 이름을 입력하세요: ";
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

	cout << "찾을 학생이 없습니다." << endl;
	system("pause");
}

void Delete(PLIST pList) {
	system("cls");
	cout << "=================== 학생삭제 ===================" << endl;

	cout << "삭제할 이름을 입력하세요: ";
	char strName[NAME_SIZE] = {};
	InputString(strName, NAME_SIZE);

	PNODE pNode = pList->pBegin;
	PNODE pPrev = NULL;

	while (pNode != NULL) {
		if (strcmp(strName, pNode->tStudent.strName) == 0) {
			// 지울 노드의 다음 노드를 얻어온다.
			PNODE pNext = pNode->pNext;

			if (pPrev == NULL) {	// 첫 번째 노드를 지운다는 의미
				delete pNode;
				pList->pBegin = pNext;

				if (pNext == NULL) {	// 노드가 하나인 경우
					pList->pEnd = NULL;
				}
			}
			else {		// 이전 노드가 있을 경우, 이전 노드의 다음을 지운 노드의 다음 노드로 연결해준다.
				delete pNode;
				pPrev->pNext = pNext;

				if (pNext == NULL) {	// 마지막 노드를 지우는 경우
					pList->pEnd = pPrev;
				}
			}
			cout << strName << " 학생 삭제 완료" << endl;
			pList->iSize--;

			system("pause");
			return;
		}
		pPrev = pNode;
		pNode = pNode->pNext;
	}
	cout << "삭제할 학생을 찾을 수 없습니다." << endl;
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