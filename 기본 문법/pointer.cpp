// ������ �̷� + �����Ϳ� �迭, void������, ����ü ������

#include <iostream>

using namespace std;

struct _tagStudent {
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() {
	/*
		������
		�Ϲ� ������ ���� �����ϰ� ������ ������ ������ �޸� �ּҸ� �����ϰ� �ȴ�. ��� ���� Ÿ���� ������ Ÿ���� ������ �� �ִ�.
		int ������ �ּҴ� int ������ ������ ������ �ؾ��Ѵ�.
		�����ʹ� �޸� �ּҸ� ��Ƴ��� �����̱� ������ x86���� ������ ���� ������ 4byte�� ������ x64�� ���� 8byte�� ���´�.

		�����ʹ� �ڱ� ������ �ƹ��� �ϵ� �� �� ����.
		�ݵ�� �ٸ� ������ �޸� �ּҸ� ������ �־�� ���� �� �� �ִµ� ������ �ִ� �� �޸� �ּҿ� �����ؼ� ���� ������ �� �ִ�.
	*/

	int iNumber = 100;

	// ���� ���� �� *�� �ٿ��ָ� �ش� Ÿ���� ������ ������ ����ȴ�.
	// ���� �տ� &�� �ٿ��ָ� �ش� ������ �޸� �ּҰ� �ȴ�.
	// pNum�� iNumber ������ �޸� �ּҸ� ������ ���� �ƴ�. �׷��Ƿ� pNum�� �̿��ؼ� iNumber�� ���� ������ �� �ְԵ� ���̴�.
	int* pNum = &iNumber;

	cout << sizeof(int*) << endl;
	cout << sizeof(char*) << endl;
	cout << sizeof(double*) << endl;

	// pNum�� �̿��ؼ� iNumber�� ���� �����غ���.
	// �������� �̿��ؼ� ���� �����⳪ ������ �� �ִ�.
	// �������� ������ ���� �տ� *�� ���̰� �Ǹ� �������� �ȴ�.
	cout << *pNum << endl;
	*pNum = 1234;

	cout << "iNumber Value: " << iNumber << endl << endl;

	cout << "iNumber Address: " << &iNumber << endl;
	cout << "pNum Value: " << pNum << endl;
	cout << "pNum Address: " << &pNum << endl;

	/*
		�����Ϳ� �迭�� ����: �迭���� �������̴�.
		�迭�� ��ü�� �ش� �迭�� �޸𸮿����� ������ �ּҸ� �ǹ��Ѵ�.
	*/

	int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };

	cout << "Array Address: " << iArray << endl;
	cout << "Array Address: " << &iArray[0] << endl;

	int* pArray = iArray;
	cout << pArray[2] << endl;

	/*
		������ ����: +, - ������ �����Ѵ�.
		++, -- �� �����ѵ� 1�� �����ϰԵǸ� �ܼ��� �޸� �ּ� ���� 1 �����ϴ� ���� �ƴϴ�.
		�޸� �ּҿ� 1�� �����ָ� ����Ű�� �ش� ������ Ÿ���� ���� Ÿ�� ũ�⸸ŭ �����ϰ� �ȴ�.
		int �������̹Ƿ� int�� ũ���� 4��ŭ ���� �����ϰ� �ȴ�.
	*/

	cout << pArray << endl;
	cout << pArray + 2 << endl;
	cout << *pArray << endl;
	cout << *(pArray + 2) << endl;
	cout << *pArray + 100 << endl;

	//char *pText = "�׽�Ʈ ���ڿ�";
	//cout << pText << endl;

	const char *pText = "�׽�Ʈ ���ڿ�";

	cout << pText << endl;
	cout << (int*)pText << endl;

	pText = "abcd";

	cout << pText << endl;
	cout << (int*)pText << endl;

	char str[8] = "abcdefg";

	cout << str << endl;
	cout << (int*)str << endl;
	

	/* ����ü ������ */
	_tagStudent tStudent = {};
	tStudent.iKor = 100;
	
	_tagStudent* pStudent = &tStudent;
	
	// ������ �켱���� ������ .�� ���� �ν��ϰ� �ȴ�. �޸� �ּ�. �� �߸��� �����̴�.
	// �׷��Ƿ� (*pStudent). �� �̿��ؼ� ����Ű�� ����� ��������� �����ؾ��Ѵ�.
	(*pStudent).iKor = 50;
	cout << tStudent.iKor << endl;

	// �޸��ּ�-> �� �̿��ؼ� ����Ű�� ����� ����� ������ �� �ִ�. (���� ����)
	pStudent->iKor = 80;
	cout << tStudent.iKor << endl;

	/*
		void ������: Ÿ���� ����.
		void* ������ �����ϰ� �Ǹ� �� ������ � Ÿ���� �޸� �ּҵ� ��� ���� �����ϴ�.
		��, �������� �Ұ����ϰ� �޸� �ּҸ� ���� �����ϴ�.
	*/
	void* pVoid = &iNumber;
	cout << "iNumber Address: " << pVoid << endl;
	//*pVoid = 10;		<- ������ �Ұ���
	int* pConvert = (int*)pVoid;	// ĳ������ ��ȯ �� ��� ����
	*pConvert = 10;
	//*((int*)pVoid) = 9999;		// ���� ����.

	cout << "iNumber: " << iNumber << endl;

	pVoid = &tStudent;

	cout << "tStudent Address: " << pVoid << endl;


	return 0;
}