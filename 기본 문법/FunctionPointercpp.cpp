// �Լ������Ϳ� C++11 Functional

#include <iostream>
#include <functional>

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

	
	/*
		Functional
		function ����� C++11���� ������ ���ִ� ����̴�.
		�� ����� �Լ������͸� ����, ��� ������ �ʰ� ���� �ּҸ� �����ؼ� ȣ������ �� �ֵ��� ������ִ� ����̴�.
		���� ���: function<��ȯŸ��(����Ÿ��)> ������; �� ���·� �����Ѵ�.
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

	// �Լ��� ���ڰ� ���� ��� placeholders �� �̿��ؼ� ������ ������ ������ �� �ִ�. �Ʒ�ó�� 2, 1�� �־��ָ� ���ڰ� ���� �ٲ�� �ȴ�.
	func3 = bind(OutSum, placeholders::_2, placeholders::_1);
	// ������ 2, 1�� �ٲ������Ƿ� 10�� b�� 20�� a�� ���� �ȴ�. -> 10 ���
	func3(10, 20);

	func4 = bind(TestFunc, placeholders::_1);
	func4(3.14f);

	return 0;
}