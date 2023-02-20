// 레퍼런스

#include <iostream>

using namespace std;

int main() {

	/*
		레퍼런스: 다른 대상을 참조하게 만들어주는 기능이다.
		참조를 하게되면 그 대상에 접근하여 값을 변경할 수 있다.
		단, 레퍼런스는 처음 레퍼런스 변수 생성 시 참조하는 대상을 꼭 지정해줘야한다.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;

	// iRefNum 레퍼런스 변수는 iNumber를 참조한다.
	int& iRefNum = iNumber;

	iRefNum = 1234;

	iRefNum = iNumber1;

	cout << iNumber << endl;

	return 0;
}