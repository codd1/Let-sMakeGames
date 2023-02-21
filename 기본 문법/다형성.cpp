// 클래스 상속과 다형성 가상함수

#include <iostream>

using namespace std;

/*
	다형성: 상속 관계에 있는 클래스 간에 서로 형변환이 가능한 성질
*/

class CParent {
public:
	CParent() {
		cout << "CParent 생성자" << endl;
	}

	~CParent() {
		cout << "CParent 소멸자" << endl;
	}

public:
	int m_iA;
protected:
	int m_iB;
private:
	int m_iC;
public:
	void Output() {
		cout << "A: " << m_iA << endl;
		cout << "B: " << m_iB << endl;
		cout << "C: " << m_iC << endl;
	}
};

class CChild : public CParent {
public:
	CChild() {
		m_iB = 200;
		//m_iC = 300;		// m_iC는 private이기 때문에 자식 내부에서도 접근 불가
		cout << "CChild 생성자" << endl;
	}

	~CChild() {
		cout << "CChild 소멸자" << endl;
	}

protected:
	int m_iD;
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
	//CParent* pParent1 = new CChild1;
	CParent* pParent2 = new CChildChild;


	// 배열로도 가능
	CParent* pParentArr[2] = {};
	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;

	// 아래 두 클래스는 모두 CParent 클래스를 상속받고 있다.
	// 그러므로 pParent를 두 타입 모두 다운캐스팅 가능하다.
	// 그런데 pParent는 CChild로 할당된 객체이다.
	// 이 객체를 CCild1 타입으로 다운캐스팅하여 넣어주게 되면 애초에 생성한 객체가 아닌 다른 타입으로 변환됐기 때문에 문제가 발생할 수 있다.
	CChild* pChild = (CChild*)pParent;		// OK
	CChild1* pCHild1 = (CChild1*)pParent;	// Error 가능

	delete pParent;
	delete pParent2;

	// 배열로도 가능
	for (int i = 0; i < 2; i++) {
		delete pParentArr[i];
	}

	return 0;
}