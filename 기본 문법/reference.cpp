// ���۷���

#include <iostream>

using namespace std;

int main() {

	/*
		���۷���: �ٸ� ����� �����ϰ� ������ִ� ����̴�.
		������ �ϰԵǸ� �� ��� �����Ͽ� ���� ������ �� �ִ�.
		��, ���۷����� ó�� ���۷��� ���� ���� �� �����ϴ� ����� �� ����������Ѵ�.
	*/
	int iNumber = 100;
	int iNumber1 = 9999;

	// iRefNum ���۷��� ������ iNumber�� �����Ѵ�.
	int& iRefNum = iNumber;

	iRefNum = 1234;

	iRefNum = iNumber1;

	cout << iNumber << endl;

	return 0;
}