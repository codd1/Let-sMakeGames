// 클래스 상속과 다형성 가상함수

#include <iostream>

using namespace std;

/*
	다형성: 상속 관계에 있는 클래스 간에 서로 형변환이 가능한 성질

	가상함수: 함수를 재정의하는 기능. 함수 오버라이딩 이라고도 부른다.
	멤버함수 앞에 virtual 키워드를 붙이면 해당 함수는 가상함수가 된다.
	만약 CParent 클래스에 virtual void output() 함수가 있다면 자식클래스에서는 이 가상함수를 재정의할 수 있다.
	재정의는 함수이름과 인자가 완전히 똑같아야한다.

	가상함수를 가지고 있는 클래스는 내부적으로 가상함수 테이블이라는 것을 생성한다. 가상함수테이블은 가상함수들의 메모리 주소를 저장하는 테이블이다.

	만약 CParent의 Output이 가상함수이고 CChild 클래스에 Output을 재정의한 후 CChild 객체를 생성하면 가상함수 테이블에는 CChild 클래스의 Output 주소가 올라가게 된다.
	만약 CParent 객체를 생성한다면 CParent의 Output 주소가 올라가게 된다.

	그래서 Output 함수, 즉 가상함수를 호출하게 되면 먼저 가상함수 테이블을 참조해서 메모리 주소를 확인한다. 가상함수테이블에 CChild의 Output 주소가 들어가 있다면 그 주소의 함수를 호출해주는 개념이다.

	소멸자도 가상함수로 만들 수 있다. 부모의 소멸자는 가상함수로 만들어두자.
*/

class CParent {
public:
	CParent() {
		cout << "CParent 생성자" << endl;
	}

	// 부모 클래스의 소멸자를 가상함수로 만들면서 자식 클래스의 소멸자도 호출되게 됐다.
	virtual ~CParent() {
		cout << "CParent 소멸자" << endl;
	}

public:
	int m_iA;
protected:
	int m_iB;
private:
	int m_iC;
public:
	virtual void Output() {
		cout << "CParent Output Function" << endl;
	}

	// 순수가상함수: 함수 뒤에 =0을 붙여주면 해당 가상함수는 순수가상함수가 된다. 순수가상함수는 구현부분이 존재하지 않는다.
	// 순수가상함수를 가지고 있는 클래스를 추상클래스라고 부른다.
	// 순수가상함수는 정의 부분이 없기 때문에 반드시 자식에서 재정의해서 사용할 목적으로 만들어주는 함수이다.

	// 추상 클래스는 인스턴스(객체) 생성이 불가능하다.
	// 추상 클래스 - 반드시 사용되어야 하는 멤버 함수를 추상 클래스에 순수 가상 함수로 선언해 놓으면, 이 클래스로부터 파생된 모든 클래스에서는 이 가상 함수를 반드시 재정의해야한다.
	virtual void OutputPure() = 0;
};

class CChild : public CParent {
public:
	CChild() {
		m_iB = 200;
		//m_iC = 300;		// m_iC는 private이기 때문에 자식 내부에서도 접근 불가
		cout << "CChild 생성자" << endl;
	}

	virtual ~CChild() {
		cout << "CChild 소멸자" << endl;
	}

protected:
	int m_iD;
public:
	void ChildOutput() {
		cout << "CChild Output Function" << endl;
	}

	virtual void Output() {
		//CParent::Output();
		cout << "CChild Output Function" << endl;
	}

	// 자식 클래스에서 이렇게 재정의해주지 않으면 오류 발생!!
	virtual void OutputPure() {

	}
};

class CChild1 :private CParent {
public:
	CChild1() {
		// private 상속을 받더라도 자식 내부에서는 접근이 가능하다.
		m_iA = 100;
		m_iB = 200;

		cout << "CChild1 생성자" << endl;
	}

	~CChild1() {
		cout << "CChild1 소멸자" << endl;
	}

private:
	int m_iD;
public:
	virtual void OutputPure() {

	}
};

class CChildChild : public CChild {
public:
	CChildChild() {
		m_iD = 500;
		cout << "CChildChild 생성자" << endl;
	}

	~CChildChild() {
		cout << "CChildChild 소멸자" << endl;
	}
private:
	int m_iE;
};

int main() {
	// CChild 클래스는 CParent 클래스를 상속받고 있다.
	// new CChild를 하게 되면 CChild 객체 하나를 생성해주고 그 메모리 주소를 반환한다.
	// 그런데 아래에서는 CParent* 타입 변수에 이 반환된 주소를 대입해주고있다.
	// 부모 포인터 타입에 CChild 객체의 메모리 주소를 넣을 수 있는 이유는 상속관계에 있기 때문이다. 자식 메모리 주소를 부모포인터타입으로 형변환된 것이기 때문이다. 이런 형변환을 업캐스팅이라고 한다.
	// 자식 -> 부모 타입 형변환: 업캐스팅
	// 부모 -> 자식 타입 형변환: 다운캐스팅
	CParent* pParent = new CChild;
	CChild1 child1;

	// CParent 클래스는 (순수가상함수를 가지고있기 때문에) 추상클래스이기 때문에 객체 생성이 불가능하다.
	//CParent* pParent1 = new CChild1;
	//CParent* pParent2 = new CChildChild;
	//CParent parent;

	// 배열로도 가능
	CParent* pParentArr[2] = {};
	//pParentArr[0] = new CChild;
	//pParentArr[1] = new CChildChild;

	// 아래 두 클래스는 모두 CParent 클래스를 상속받고 있다.
	// 그러므로 pParent를 두 타입 모두 다운캐스팅 가능하다.
	// 그런데 pParent는 CChild로 할당된 객체이다.
	// 이 객체를 CCild1 타입으로 다운캐스팅하여 넣어주게 되면 애초에 생성한 객체가 아닌 다른 타입으로 변환됐기 때문에 문제가 발생할 수 있다.
	CChild* pChild = (CChild*)pParent;		// OK
	CChild1* pCHild1 = (CChild1*)pParent;	// Error 가능

	// CChild 클래스에 있는 ChildOutput 함수에 접근할 수 없다.
	// Why? "pParent는 CParent 포인터 타입"이기 때문에 자식 멤버에 접근이 불가능하다. 만약 접근하고 싶다면 형변환 해야한다.
	//((CChild*)pParent)->ChildOutput();

	// CChild에서 Output 함수가 재정의 되어있기 때문에 CChild의 Output 함수가 실행된다. (자식에서 재정의 되어있지 않으면 부모 Output함수 호출)
	pParent->Output();

	// 부모 클래스의 Output 함수를 호출하고 싶은 경우
	//pParent->CParent::Output();

	// 현재 delete를 하게 되면 CChild 소멸자 -> CParent 소멸자가 호출되어야하는데 지금은 CParent 소멸자만 호출된다.
	// Why? 근본적으로 "pParent는 CParent 포인터 타입"이기 때문에 CChild 소멸자가 호출될 수 없다.
	delete pParent;
	//delete pParent2;

	// 배열로도 가능
	for (int i = 0; i < 2; i++) {
		//delete pParentArr[i];
	}

	return 0;
}