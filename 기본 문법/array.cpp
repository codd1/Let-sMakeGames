// �迭 (+do while)

#include <iostream>

using namespace std;

int main() {
	/*
		do while��: �ݺ����� �� ����
		while���� ó�� ���Ժ��� ���ǽ��� üũ������ do while�� ó�� �� ���� ������ ������ �ǰ�
		�� �Ŀ� ���ǽ��� üũ�ؼ� true�� ��� ���۵Ǵ� �ݺ����̴�.
	*/

	int iNumber = 0;
	do {
		cout << iNumber << endl;		// ������ ����
		cout << endl;
	} while (iNumber > 0);

	/*
		�迭: ���� ���� ������ �� ���� �������� �� �ִ� ���
		�迭�� Ư¡: ���ӵ� �޸� ���� ������ �Ҵ�ȴ�.
	*/
	// int iArray[10] = { 1,2,3,4,5,6,7,8,9,10 };
	// ����ִ� �߰�ȣ�� ������ ��� ��� �ε����� 0���� �ʱ�ȭ�Ѵ�.
	int iArray[10] = {};
	iArray[1] = 1234;
	
	cout << "1���� �迭" << endl;
	for (int i = 0; i < 10; i++) {
		cout << iArray[i] << endl;
	}
	cout << endl;

	int iArray2[10][10] = { {1,2,3},{4,5,6} };

	cout << "2���� �迭" << endl;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << iArray2[i][j] << "\t";
		}
		cout << endl;
	}

	return 0;
}