// for���� ��øfor��

#include <iostream>

using namespace std;

int main() {
	// for��

	for (int i = 0; i < 10; i++) {
		cout << i << endl;
	}

	// ������ 2�� ���
	for (int i = 1; i <= 9; i++) {
		cout << "2 * " << i << " = " << 2 * i << endl;
	}

	// 1~100 ������ ���� �� ¦���� ����ϴ� for��
	for (int i = 2; i <= 100; i=i+2) {
		cout << i << endl;
	}

	// 1~100 ������ ���� �� 3�� 7�� ������� ����ϴ� for��
	for (int i = 1; i <= 100; i++) {
		if (i % 21 == 0) {	// i % 3 == 0 && i % 7 == 0
			cout << i << endl;
		}
	}

	// ��ø for��: for�� �ȿ� �� �ٸ� for���� �����ϴ� ����
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cout << "i = " << i << " j = " << j << endl;
		}
	}

	return 0;
}