// 함수 + 지역변수, 전역변수

#include <iostream>

using namespace std;

// 코드블럭 외부에 변수를 선언하게 되면 전역변수가 된다.
// 전역 변수는 이 변수를 선언한 아래의 모든 부분에서 공유해서 사용이 가능하다.
// 전역변수는 소속된 코드블럭이 없으므로 프로그램이 종료될 때까지 메모리에 존재하게되고 프로그램이 종료될 때 메모리에서 해제된다.
int g_iNum = 123;


/*
	함수: 기능을 만들어준다.
	특정 상황에 동작하는 코드 집합을 만들어내는 것이다.
	함수명은 가급적이면 이 함수가 하는 역할을 정확하게 표시해주는 것이 코드 가독성에 좋다.

*/

// Call by Value
int Sum(int a, int b) {
	// return 키워드를 이용해서 이 함수의 반환 타입에 맞는 값을 반환해야한다.
	return a + b;
}

// 함수는 단순히 만들어놓기만해서는 작동하지 않는다.
// 메인 함수에서 호출해야 작동한다.
void OutputText() {
	cout << "OutputText Function!!" << endl;
}

void OutputNumber(int iNumber) {
	cout << "Number: " << iNumber << endl;
}

// 아래 함수처럼 인자를 넘겨받게 될 경우 이 인자는 이 함수의 지역변수가 되고 stack에 할당된다.
// 할당된 지역변수는 해당 지역변수가 소속된 코드블럭이 닫히게 되면 메모리에서 해제된다.
void ChangeNumber(int iNumber) {
	iNumber = 9999;			// Call by Value로는 값이 바뀌지 않는다.
	g_iNum = 456;
}

/*
	함수의 오버로딩: 같은 이름의 함수지만 기능이 다르던가 인자가 다른 함수를 말한다.
	오버로딩의 조건: 함수 이름이 무조건 같아야한다. 단, 인자의 갯수 혹은 타입이 달라야 오버로딩이 성립된다.
	반환타입은 오버로딩에 영향을 주지 않는다.
*/

// 아래 함수는 결과값을 인자로 받아와서 결과를 반환해주었다. 이런 형태의 함수를
// Call by Address라고 한다.
void ChangeNumber(int* pNumber) {
	*pNumber = 7777;
}


/*
	함수의 디폴트인자
	인자에 기본값을 대입해두면 인자를 넘겨주지 않을 경우 기본 설정한 값이 되고 인자를 넘겨줄 경우 넘겨받은 값으로 인자를 설정하게된다.
	디폴트인자는 가장 오른쪽부터 지정해주어야한다.
*/
void Output(int iNum1, int iNum2 = 10) {
	cout << iNum1 << endl;
	cout << iNum2 << endl;
}

int main() {

	cout << Sum(10, 20) << endl;

	OutputText();
	OutputNumber(1234);

	// 아래처럼 특정 코드블럭 안에서 선언되는 변수를 지역변수라고 한다.
	// 지역변수는 메모리 영역 중 stack에 할당된다.
	int iNumber = 0;
	ChangeNumber(iNumber);		// Call by Value
	cout << "iNumber: " << iNumber << endl;

	ChangeNumber(&iNumber);	// Call by Address
	cout << "iNumber: " << iNumber << endl;

	Output(30);

	cout << "전역변수 g_iNum: " << g_iNum << endl;

	return 0;
}