// 구조체와 문자열함수

/*
	구조체: 관련있는 변수들을 모아서 하나의 새로운 타입을 만들어주는 기능
			사용자 정의 변수 타입
	배열과 구조체의 공통점
		> 1. 데이터의 집합이다.
		> 2. 연속된 메모리 블럭에 할당된다. 구조체 멤버(변수)들은 연속된 메모리 블럭에 할당된다.
*/
#include <iostream>

#define NAME_SIZE 32

using namespace std;

struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() {
	_tagStudent tStudent;
	_tagStudent tStudentArr[100] = {};

	// 구조체 멤버에 접근할 때는 .을 이용해서 접근한다.
	tStudent.iKor = 100;

	//tStudent.strName = "ajkgjlsdkf";
	// 문자열을 배열에 넣어줄 때는 단순 대입으로 불가능하므로
	// strcpy_s 라는 함수를 이용해서 문자열을 복사해줘야한다.
	// 오른쪽에 있는 문자열을 왼쪽으로 복사해준다.
	// 문자열의 끝은 항상 0(NULL)로 끝나야한다.
	strcpy_s(tStudent.strName, "가나다라 asdf");

	// strcat_s 함수는 문자열을 붙여주는 기능이다.
	// 오른쪽에 이쓴 문자열을 왼쪽에 붙여준다.
	strcat_s(tStudent.strName, " 문자열 붙이기");

	// strcmp 함수는 두 문자열을 비교하여 같을 경우 0을 반환하고 다를 경우 0이 아닌 값을 반환한다.
	strcpy_s(tStudent.strName, "홍길동");
	cout << "비교할 이름을 입력하세요: ";
	char strName[NAME_SIZE] = {};
	cin >> strName;
	
	if (strcmp(tStudent.strName, strName) == 0) {
		cout << "학생을 찾았습니다." << endl;
	}
	else {
		cout << "찾는 학생이 없습니다." << endl;
	}



	cout << "이름: " << tStudent.strName << endl;
	cout << "학번: " << tStudent.iNumber << endl;
	cout << "국어: " << tStudent.iKor << endl;
	cout << "수학: " << tStudent.iMath << endl;
	cout << "영어: " << tStudent.iEng << endl;

	return 0;
}