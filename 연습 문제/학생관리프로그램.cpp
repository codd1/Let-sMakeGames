// 구조체를 이용한 학생관리프로그램1

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

		// 메뉴를 출력한다.
		cout << "1. 학생등록" << endl;
		cout << "2. 학생삭제" << endl;
		cout << "3. 학생탐색" << endl;
		cout << "4. 학생출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요: ";
		
		int iMenu;
		cin >> iMenu;

		// cin은 변수 타입에 맞춰서 값을 입력해야하는데 다른 타입의 문자를 입력할 경우 에러가 발생한다.
		// 그렇게 때문에 예외처리로 에러가 발생했는지를 여기서 체크하여 에러가 발생하면 cin 내부의 에러버퍼를 비워준다.
		// cin 내부에 입력버퍼가 있는데 입력버퍼는 입력한 값을 저장해놓고 그 값을 변수에 넣어주는 역할을 한다.
		// 이 입력버퍼에 \n이 남아있으므로 버퍼를 순회하여 \n을 지워준다.
		// 버퍼: 임시저장공간
		// 먼저 에러를 체크한다. cin.fail()을 했을 때 입력 에러가 발생할 경우 true를 반환한다.
		if (cin.fail()) {
			// 에러 버퍼를 비워준다.
			cin.clear();

			// 입력 버퍼에 \n이 남아있으므로 입력버퍼를 검색해 \n을 지워준다.
			// cin.ignore(검색하고자하는 버퍼 크기, 찾는 문자);
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MENU_EXIT) {
			break;
		}

		switch (iMenu) {
		case MENU_INSERT:
			system("cls");
			cout << "============ 학생 추가 ============" << endl;
			// 학생 정보를 추가한다. 이름, 주소, 전화번호, 점수를 입력 받고 학번, 총점, 평균은 연산을 통해 계산해준다.

			// 더 이상 등록할 수 없을 경우 (등록 최대치) 등록 불가
			if (iStudentCount == STUDENT_MAX) {
				break;
			}
			cout << "이름: ";
			cin >> tStudentArr[iStudentCount].strName;

			cout << "주소: ";
			cin.ignore(1024, '\n');
			cin.getline(tStudentArr[iStudentCount].strAdress, ADDRESS_SIZE);

			cout << "전화번호: ";
			cin.getline(tStudentArr[iStudentCount].strPhoneNumber, PHONE_SIZE);

			cout << "국어: ";
			cin >> tStudentArr[iStudentCount].iKor;

			cout << "수학: ";
			cin >> tStudentArr[iStudentCount].iMath;

			cout << "영어: ";
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

			cout << "학생 추가 완료" << endl;
			break;

		case MENU_DELETE:
			system("cls");
			cout << "============ 학생 삭제 ============" << endl;

			cin.ignore(1024, '\n');
			cout << "삭제할 이름을 입력하세요: ";
			cin.getline(strSearchName, NAME_SIZE);

			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					for (int j = i; j < iStudentCount - 1; j++) {
						tStudentArr[i] = tStudentArr[i + 1];
					}
					iStudentCount--;

					cout << "학생 정보를 삭제했습니다." << endl;
					break;
				}
			}
			break;

		case MENU_SEARCH:
			system("cls");
			cout << "============ 학생 탐색 ============" << endl;	

			cin.ignore(1024, '\n');
			cout << "탐색할 이름을 입력하세요: ";
			cin.getline(strSearchName, NAME_SIZE);
			
			for (int i = 0; i < iStudentCount; i++) {
				if (strcmp(tStudentArr[i].strName, strSearchName) == 0) {
					cout << "이름: " << tStudentArr[i].strName << endl;
					cout << "주소: " << tStudentArr[i].strAdress << endl;
					cout << "전화번호: " << tStudentArr[i].strPhoneNumber << endl;
					cout << "학번: " << tStudentArr[i].iNumber << endl;
					cout << "국어: " << tStudentArr[i].iKor << endl;
					cout << "수학: " << tStudentArr[i].iMath << endl;
					cout << "영어: " << tStudentArr[i].iEng << endl;
					cout << "총점: " << tStudentArr[i].iTotal << endl;
					cout << "평균: " << tStudentArr[i].fAvg << endl << endl;
					break;
				}
			}
			break;

		case MENU_OUTPUT:
			system("cls");
			cout << "============ 학생 출력 ============" << endl;

			for (int i = 0; i < iStudentCount; i++) {
				cout << "이름: " << tStudentArr[i].strName << endl;
				cout << "주소: " << tStudentArr[i].strAdress << endl;
				cout << "전화번호: " << tStudentArr[i].strPhoneNumber << endl;
				cout << "학번: " << tStudentArr[i].iNumber << endl;
				cout << "국어: " << tStudentArr[i].iKor << endl;
				cout << "수학: " << tStudentArr[i].iMath << endl;
				cout << "영어: " << tStudentArr[i].iEng << endl;
				cout << "총점: " << tStudentArr[i].iTotal << endl;
				cout << "평균: " << tStudentArr[i].fAvg << endl << endl;
			}

			break;

		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}