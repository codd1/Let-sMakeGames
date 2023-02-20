// 클래스

#include <iostream>

using namespace std;

/*
	객체(object): 모든 사물을 의미한다. C++에서 각 변수들은 객체로 취급할 수 있다.
	하지만 객체지향 프로그래밍을 지원하기위해 제공되는 수단은 class이다. class는 객체를 만들기 위한 틀이다. (class != 객체)
	객체지향 프로그래밍(OOP): 객체들의 관계를 설정해주어서 부품을 조립하듯이 객체들을 조립하여 완성된 프로그램을 만들어나가는 방식이다.

	클래스의 4가지 속성
	캡슐화: 클래스 안에 속하는 여러 변수 혹은 함수를 하나의 클래스로 묶어주는 기능
	은닉화: 클래스 안에 속하는 변수 혹은 함수를 내가 원하는 부분만 외부에 공개하고 외부에 공개하지 않을 수 있다.
		- public: 클래스 내부와 외부에서 모두 접근 가능한 방법
		- protected: 클래스 외부에서는 접근이 불가능하고 자기자신 내부나 자식 클래스 내부에서는 접근이 가능한 방법
		- private: 자기자신 내부에서만 접근이 가능하고 외부나 자식 내부에서는 접근이 불가능한 방법
	상속성: 클래스는 클래스와 클래스 간에 부모, 자식 관계를 형성할 수 있다.
			자식 클래스는 부모클래스의 멤버를 물려받아 자신의 것처럼 사용할 수 있다. 단, private로 되어 있는 멤버에는 접근이 불가능하다.
	다형성: 부모 자식관계로 상속관계가 형성되어 있는 클래스 간에 서로 형변환이 가능한 성질을 말한다.

	생성자와 소멸자
	생성자: 어떤 클래스를 이용해서 객체를 생성할 때 자동으로 호출되는 함수이다. 객체 생성 시 호출되는 함수이기 때문에 객체의 멤버변수를 초기화할 때 유용하게 사용할 수 있다.
	생성자를 만들어주지 않을 경우 내부적으로 기본 생성자가 제공 되어 기본 생성자를 자동으로 호출해주게 된다.
	클래스명(){

	} 의 형태

	소멸자: 어떤 클래스를 이용해서 생성한 객체가 메모리에서 해제될 때(여기서는 메인 함수가 종료될 때) 자동으로 호출되는 함수이다. 객체를 사용하고 난 뒤 마무리 작업을 해줄 때 유용하게 사용할 수 있다.
	~클래스명(){

	} 의 형태
*/

class CPlayer {

public:		// private이면 메인함수에서 접근이 불가능해 오류 발생!
	CPlayer() {			// 생성자
		cout << "Player 생성자" << endl;
		strcpy_s(m_strName, "플레이어");
	}

	CPlayer(const char* pName) {		// 오버로딩
		strcpy_s(m_strName, pName);
		cout << "Name 생성자" << endl;
	}

	CPlayer(const char* pName, int iFlash, int iBack) :		// 오버로딩
		m_iBack(iBack),
		m_iFlash(iFlash)
	{
		strcpy_s(m_strName, pName);
		//m_iFlash = iFlash;

		cout << "Name, Flash, Back 생성자" << endl;
	}

	~CPlayer() {		// 소멸자
		cout << "Player 소멸자" << endl;
	}
	// 클래스 멤버변수를 선언할 때는 m_을 붙여준다. (개인 스타일)
	char m_strName[32];

public:		// public 키워드 아래에 있는 멤버는 모두 외부에서 접근이 가능하다.
	int m_iAttack;
	int m_iHP;

private:
	int m_iFlash;
	int m_iBack;

public:
	void Output() {
		cout << "Player Output" << endl;
		cout << "Name: " << m_strName << endl;
	}

};

int main() {
	CPlayer ply1("coddl", 3, 1);

	// main() 함수 안은 클래스 외부이기 때문에 public으로 설정되어있는 멤버에만 접근이 가능하다.
	// ply1.m_iFlash;	// Error!
	ply1.Output();

	return 0;
}