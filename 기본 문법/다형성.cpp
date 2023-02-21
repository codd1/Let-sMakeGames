// Ŭ���� ��Ӱ� ������ �����Լ�

#include <iostream>

using namespace std;

/*
	������: ��� ���迡 �ִ� Ŭ���� ���� ���� ����ȯ�� ������ ����

	�����Լ�: �Լ��� �������ϴ� ���. �Լ� �������̵� �̶�� �θ���.
	����Լ� �տ� virtual Ű���带 ���̸� �ش� �Լ��� �����Լ��� �ȴ�.
	���� CParent Ŭ������ virtual void output() �Լ��� �ִٸ� �ڽ�Ŭ���������� �� �����Լ��� �������� �� �ִ�.
	�����Ǵ� �Լ��̸��� ���ڰ� ������ �Ȱ��ƾ��Ѵ�.

	�����Լ��� ������ �ִ� Ŭ������ ���������� �����Լ� ���̺��̶�� ���� �����Ѵ�. �����Լ����̺��� �����Լ����� �޸� �ּҸ� �����ϴ� ���̺��̴�.

	���� CParent�� Output�� �����Լ��̰� CChild Ŭ������ Output�� �������� �� CChild ��ü�� �����ϸ� �����Լ� ���̺��� CChild Ŭ������ Output �ּҰ� �ö󰡰� �ȴ�.
	���� CParent ��ü�� �����Ѵٸ� CParent�� Output �ּҰ� �ö󰡰� �ȴ�.

	�׷��� Output �Լ�, �� �����Լ��� ȣ���ϰ� �Ǹ� ���� �����Լ� ���̺��� �����ؼ� �޸� �ּҸ� Ȯ���Ѵ�. �����Լ����̺� CChild�� Output �ּҰ� �� �ִٸ� �� �ּ��� �Լ��� ȣ�����ִ� �����̴�.

	�Ҹ��ڵ� �����Լ��� ���� �� �ִ�. �θ��� �Ҹ��ڴ� �����Լ��� ��������.
*/

class CParent {
public:
	CParent() {
		cout << "CParent ������" << endl;
	}

	// �θ� Ŭ������ �Ҹ��ڸ� �����Լ��� ����鼭 �ڽ� Ŭ������ �Ҹ��ڵ� ȣ��ǰ� �ƴ�.
	virtual ~CParent() {
		cout << "CParent �Ҹ���" << endl;
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

	// ���������Լ�: �Լ� �ڿ� =0�� �ٿ��ָ� �ش� �����Լ��� ���������Լ��� �ȴ�. ���������Լ��� �����κ��� �������� �ʴ´�.
	// ���������Լ��� ������ �ִ� Ŭ������ �߻�Ŭ������� �θ���.
	// ���������Լ��� ���� �κ��� ���� ������ �ݵ�� �ڽĿ��� �������ؼ� ����� �������� ������ִ� �Լ��̴�.

	// �߻� Ŭ������ �ν��Ͻ�(��ü) ������ �Ұ����ϴ�.
	// �߻� Ŭ���� - �ݵ�� ���Ǿ�� �ϴ� ��� �Լ��� �߻� Ŭ������ ���� ���� �Լ��� ������ ������, �� Ŭ�����κ��� �Ļ��� ��� Ŭ���������� �� ���� �Լ��� �ݵ�� �������ؾ��Ѵ�.
	virtual void OutputPure() = 0;
};

class CChild : public CParent {
public:
	CChild() {
		m_iB = 200;
		//m_iC = 300;		// m_iC�� private�̱� ������ �ڽ� ���ο����� ���� �Ұ�
		cout << "CChild ������" << endl;
	}

	virtual ~CChild() {
		cout << "CChild �Ҹ���" << endl;
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

	// �ڽ� Ŭ�������� �̷��� ������������ ������ ���� �߻�!!
	virtual void OutputPure() {

	}
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
public:
	virtual void OutputPure() {

	}
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
	CChild1 child1;

	// CParent Ŭ������ (���������Լ��� �������ֱ� ������) �߻�Ŭ�����̱� ������ ��ü ������ �Ұ����ϴ�.
	//CParent* pParent1 = new CChild1;
	//CParent* pParent2 = new CChildChild;
	//CParent parent;

	// �迭�ε� ����
	CParent* pParentArr[2] = {};
	//pParentArr[0] = new CChild;
	//pParentArr[1] = new CChildChild;

	// �Ʒ� �� Ŭ������ ��� CParent Ŭ������ ��ӹް� �ִ�.
	// �׷��Ƿ� pParent�� �� Ÿ�� ��� �ٿ�ĳ���� �����ϴ�.
	// �׷��� pParent�� CChild�� �Ҵ�� ��ü�̴�.
	// �� ��ü�� CCild1 Ÿ������ �ٿ�ĳ�����Ͽ� �־��ְ� �Ǹ� ���ʿ� ������ ��ü�� �ƴ� �ٸ� Ÿ������ ��ȯ�Ʊ� ������ ������ �߻��� �� �ִ�.
	CChild* pChild = (CChild*)pParent;		// OK
	CChild1* pCHild1 = (CChild1*)pParent;	// Error ����

	// CChild Ŭ������ �ִ� ChildOutput �Լ��� ������ �� ����.
	// Why? "pParent�� CParent ������ Ÿ��"�̱� ������ �ڽ� ����� ������ �Ұ����ϴ�. ���� �����ϰ� �ʹٸ� ����ȯ �ؾ��Ѵ�.
	//((CChild*)pParent)->ChildOutput();

	// CChild���� Output �Լ��� ������ �Ǿ��ֱ� ������ CChild�� Output �Լ��� ����ȴ�. (�ڽĿ��� ������ �Ǿ����� ������ �θ� Output�Լ� ȣ��)
	pParent->Output();

	// �θ� Ŭ������ Output �Լ��� ȣ���ϰ� ���� ���
	//pParent->CParent::Output();

	// ���� delete�� �ϰ� �Ǹ� CChild �Ҹ��� -> CParent �Ҹ��ڰ� ȣ��Ǿ���ϴµ� ������ CParent �Ҹ��ڸ� ȣ��ȴ�.
	// Why? �ٺ������� "pParent�� CParent ������ Ÿ��"�̱� ������ CChild �Ҹ��ڰ� ȣ��� �� ����.
	delete pParent;
	//delete pParent2;

	// �迭�ε� ����
	for (int i = 0; i < 2; i++) {
		//delete pParentArr[i];
	}

	return 0;
}