// �Լ������Ϳ� C++11 Functional

#include <iostream>

using namespace std;

/*
	�Լ�������: �Լ��� �޸� �ּҸ� �����ϱ� ���� ������ ������ ������ �� �ִ�.
	�����Լ��� ��� �Լ����� �� �Լ��� �޸� �ּ��̴�. (�迭ó��)
	�Լ������� ������:
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
		// this-> �� ��������
		cout << "Test: " << this->m_iTest << endl;
	}
};

int main() {
	int (*pFunc)(int, int) = Sum;

	cout << pFunc(10, 20) << endl;

	pFunc = OutSum;

	OutSum(10, 20);

	//pFunc = Output();		// Error! ��ȯŸ��mismatch
	void(*pFunc1)() = Output;
	pFunc1();



	CPlayer ply1, ply2;

	ply1.m_iTest = 100;
	ply2.m_iTest = 200;

	// this ������: Ŭ���� �ȿ��� this�� ����� ��� �ش� ��ü�� �޸� �ּҰ� �ȴ�. ��, �ڱ��ڽ��� �������̴�.
	// ����Լ��� ȣ���� �� this�� ȣ���ڷ� �����Ѵ�.
	ply1.Output();
	ply2.Output();

	// ����Լ������� ���� �� �����ͺ��� �̸� �տ� Ŭ������:: �� �ٿ��ش�.
	void (CPlayer:: * pFunc2)() = &CPlayer::Output;

	(ply1.*pFunc2)();
	
	return 0;
}