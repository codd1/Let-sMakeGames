// 함수포인터와 C++11 Functional

#include <iostream>

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
	
	return 0;
}