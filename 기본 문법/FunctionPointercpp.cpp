// 함수포인터와 C++11 Functional

#include <iostream>
#include <functional>

using namespace std;

/*
	함수포인터: 함수의 메모리 주소를 저장하기 위한 포인터 변수를 선언할 수 있다.
	전역함수의 경우 함수명이 곧 함수의 메모리 주소이다. (배열처럼)
	함수포인터 선언방법:
*/

int Sum(int a, int b) {
	return a + b;
}

int OutSum(int a, int b) {
	cout << a - b << endl;
	return a - b;
}

void Output() {
	cout << "Output Function" << endl;
}

float TestFunc(float a) {
	cout << a << endl;
	return a;
}

class CPlayer {
public:
	CPlayer() {
		m_iTest = 10;
	}

	~CPlayer() {

	}
public:
	int m_iTest;
public:
	void Output() {
		cout << "Player" << endl;
		// this-> 는 생략가능
		cout << "Test: " << this->m_iTest << endl;
	}
};

int main() {
	int (*pFunc)(int, int) = Sum;

	cout << pFunc(10, 20) << endl;

	pFunc = OutSum;

	OutSum(10, 20);

	//pFunc = Output();		// Error! 반환타입mismatch
	void(*pFunc1)() = Output;
	pFunc1();



	CPlayer ply1, ply2;

	ply1.m_iTest = 100;
	ply2.m_iTest = 200;

	// this 포인터: 클래스 안에서 this를 사용할 경우 해당 객체의 메모리 주소가 된다. 즉, 자기자신의 포인터이다.
	// 멤버함수를 호출할 때 this를 호출자로 세팅한다.
	ply1.Output();
	ply2.Output();

	// 멤버함수포인터 선언 시 포인터변수 이름 앞에 클래스명:: 을 붙여준다.
	void (CPlayer:: * pFunc2)() = &CPlayer::Output;

	(ply1.*pFunc2)();

	
	/*
		Functional
		function 기능은 C++11부터 지원을 해주는 기능이다.
		이 기능은 함수포인터를 전역, 멤버 가리지 않고 쉽게 주소를 저장해서 호출해줄 수 있도록 만들어주는 기능이다.
		선언 방법: function<반환타입(인자타입)> 변수명; 의 형태로 선언한다.
	*/

	function<void()> func;
	function<void()> func1;

	func = bind(Output);
	func1 = bind(&CPlayer::Output, &ply1);

	cout << "============= Functional =============" << endl;

	func();
	func1();

	function<int(int, int)> func3;
	function<float(float)> func4;

	// 함수에 인자가 있을 경우 placeholders 를 이용해서 인자의 순서를 정의할 수 있다. 아래처럼 2, 1로 넣어주면 인자가 서로 바뀌게 된다.
	func3 = bind(OutSum, placeholders::_2, placeholders::_1);
	// 위에서 2, 1로 바꿔줬으므로 10은 b에 20은 a에 들어가게 된다. -> 10 출력
	func3(10, 20);

	func4 = bind(TestFunc, placeholders::_1);
	func4(3.14f);

	return 0;
}