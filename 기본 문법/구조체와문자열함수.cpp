// ����ü�� ���ڿ��Լ�

/*
	����ü: �����ִ� �������� ��Ƽ� �ϳ��� ���ο� Ÿ���� ������ִ� ���
			����� ���� ���� Ÿ��
	�迭�� ����ü�� ������
		> 1. �������� �����̴�.
		> 2. ���ӵ� �޸� ���� �Ҵ�ȴ�. ����ü ���(����)���� ���ӵ� �޸� ���� �Ҵ�ȴ�.
*/
#include <iostream>

#define NAME_SIZE 32

using namespace std;

struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() {
	_tagStudent tStudent;
	_tagStudent tStudentArr[100] = {};

	// ����ü ����� ������ ���� .�� �̿��ؼ� �����Ѵ�.
	tStudent.iKor = 100;

	//tStudent.strName = "ajkgjlsdkf";
	// ���ڿ��� �迭�� �־��� ���� �ܼ� �������� �Ұ����ϹǷ�
	// strcpy_s ��� �Լ��� �̿��ؼ� ���ڿ��� ����������Ѵ�.
	// �����ʿ� �ִ� ���ڿ��� �������� �������ش�.
	// ���ڿ��� ���� �׻� 0(NULL)�� �������Ѵ�.
	strcpy_s(tStudent.strName, "�����ٶ� asdf");

	// strcat_s �Լ��� ���ڿ��� �ٿ��ִ� ����̴�.
	// �����ʿ� �̾� ���ڿ��� ���ʿ� �ٿ��ش�.
	strcat_s(tStudent.strName, " ���ڿ� ���̱�");

	// strcmp �Լ��� �� ���ڿ��� ���Ͽ� ���� ��� 0�� ��ȯ�ϰ� �ٸ� ��� 0�� �ƴ� ���� ��ȯ�Ѵ�.
	strcpy_s(tStudent.strName, "ȫ�浿");
	cout << "���� �̸��� �Է��ϼ���: ";
	char strName[NAME_SIZE] = {};
	cin >> strName;
	
	if (strcmp(tStudent.strName, strName) == 0) {
		cout << "�л��� ã�ҽ��ϴ�." << endl;
	}
	else {
		cout << "ã�� �л��� �����ϴ�." << endl;
	}



	cout << "�̸�: " << tStudent.strName << endl;
	cout << "�й�: " << tStudent.iNumber << endl;
	cout << "����: " << tStudent.iKor << endl;
	cout << "����: " << tStudent.iMath << endl;
	cout << "����: " << tStudent.iEng << endl;

	return 0;
}