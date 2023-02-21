// Ŭ���� ��Ӱ� ������ �����Լ�

#include <iostream>

using namespace std;

/*
	������: ��� ���迡 �ִ� Ŭ���� ���� ���� ����ȯ�� ������ ����
*/

class CParent {
public:
	CParent() {
		cout << "CParent ������" << endl;
	}

	~CParent() {
		cout << "CParent �Ҹ���" << endl;
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
		//m_iC = 300;		// m_iC�� private�̱� ������ �ڽ� ���ο����� ���� �Ұ�
		cout << "CChild ������" << endl;
	}

	~CChild() {
		cout << "CChild �Ҹ���" << endl;
	}

protected:
	int m_iD;
};

class CChild1 :private CParent {
public:
	CChild1() {
		// private ����� �޴��� �ڽ� ���ο����� ������ �����ϴ�.
		m_iA = 100;
		m_iB = 200;

		cout << "CChild1 ������" << endl;
	}

	~CChild1() {
		cout << "CChild1 �Ҹ���" << endl;
	}

private:
	int m_iD;
};

class CChildChild : public CChild {
public:
	CChildChild() {
		m_iD = 500;
		cout << "CChildChild ������" << endl;
	}

	~CChildChild() {
		cout << "CChildChild �Ҹ���" << endl;
	}
private:
	int m_iE;
};

int main() {
	// CChild Ŭ������ CParent Ŭ������ ��ӹް� �ִ�.
	// new CChild�� �ϰ� �Ǹ� CChild ��ü �ϳ��� �������ְ� �� �޸� �ּҸ� ��ȯ�Ѵ�.
	// �׷��� �Ʒ������� CParent* Ÿ�� ������ �� ��ȯ�� �ּҸ� �������ְ��ִ�.
	// �θ� ������ Ÿ�Կ� CChild ��ü�� �޸� �ּҸ� ���� �� �ִ� ������ ��Ӱ��迡 �ֱ� �����̴�. �ڽ� �޸� �ּҸ� �θ�������Ÿ������ ����ȯ�� ���̱� �����̴�. �̷� ����ȯ�� ��ĳ�����̶�� �Ѵ�.
	// �ڽ� -> �θ� Ÿ�� ����ȯ: ��ĳ����
	// �θ� -> �ڽ� Ÿ�� ����ȯ: �ٿ�ĳ����
	CParent* pParent = new CChild;
	//CParent* pParent1 = new CChild1;
	CParent* pParent2 = new CChildChild;


	// �迭�ε� ����
	CParent* pParentArr[2] = {};
	pParentArr[0] = new CChild;
	pParentArr[1] = new CChildChild;

	// �Ʒ� �� Ŭ������ ��� CParent Ŭ������ ��ӹް� �ִ�.
	// �׷��Ƿ� pParent�� �� Ÿ�� ��� �ٿ�ĳ���� �����ϴ�.
	// �׷��� pParent�� CChild�� �Ҵ�� ��ü�̴�.
	// �� ��ü�� CCild1 Ÿ������ �ٿ�ĳ�����Ͽ� �־��ְ� �Ǹ� ���ʿ� ������ ��ü�� �ƴ� �ٸ� Ÿ������ ��ȯ�Ʊ� ������ ������ �߻��� �� �ִ�.
	CChild* pChild = (CChild*)pParent;		// OK
	CChild1* pCHild1 = (CChild1*)pParent;	// Error ����

	delete pParent;
	delete pParent2;

	// �迭�ε� ����
	for (int i = 0; i < 2; i++) {
		delete pParentArr[i];
	}

	return 0;
}