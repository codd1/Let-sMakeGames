// 배열 (+do while)

#include <iostream>

using namespace std;

int main() {
	/*
		do while문: 반복문의 한 종류
		while문은 처음 진입부터 조건식을 체크하지만 do while은 처음 한 번은 무조건 동작이 되고
		그 후에 조건식을 체크해서 true일 경우 동작되는 반복문이다.
	*/

	int iNumber = 0;
	do {
		cout << iNumber << endl;		// 무조건 실행
		cout << endl;
	} while (iNumber > 0);

	/*
		배열: 여러 개의 변수를 한 번에 생성해줄 수 있는 기능
		배열의 특징: 연속된 메모리 블럭에 공간이 할당된다.
	*/
	// int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };
	// 비어있는 중괄호를 대입할 경우 모든 인덱스를 0으로 초기화한다.
	int iArray[10] = {};
	iArray[1] = 1234;
	
	cout << "1차원 배열" << endl;
	for (int i = 0; i < 10; i++) {
		cout << iArray[i] << endl;
	}
	cout << endl;

	int iArray2[10][10] = { {1,2,3},{4,5,6} };

	cout << "2차원 배열" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << iArray2[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}