// �߱�����

/*
	����: �߱����� �����
	1~9 ������ ������ ���� 3���� ���´�. ��, ���ڴ� �ߺ��Ǹ� �ȵȴ�.
	3���� ���ڴ� * * *�� ���·� ��µǰ� �� 3���� ���ڸ� ���ߴ� �����̴�.
	����ڴ� �� 3���� ���ڸ� ���� ������ ����ؼ� 3���� ���ڸ� �Է��Ѵ�.
	���� ������� ���ڰ� 7 3 8�� ��� ����ڴ� 3���� ���ڸ� ��� �Է��Ѵ�.
	�Է�: 1 2 4 �� �Է����� ���, 1 2 4�� ������� ���� �� �ƹ� �͵� �����Ƿ� Out �� ����Ѵ�.

	�Է�: 7 5 9�� �Է����� ��� 7�� ������� ���� �� �ְ� ��ġ�� �����Ƿ� strike�̳�, 5 9�� �����Ƿ� ����� 1strike 0ball�� ����Ѵ�.

	�Է�: 7 8 6�� �Է����� ��� 7�� ������� ���� �� �ְ� ��ġ�� �����Ƿ� strike�̰� 8�� ���ڴ� ������ ��ġ�� �ٸ��Ƿ� 1strike 1ball�� ����Ѵ�.

	�̷��� ����� �ϰ� �Է��� �����鼭 ���������� 3���� ���ڸ� �ڸ����� ��� �˸°� �Է��ϸ� ������ ����ȴ�.
	���� �Է¹��� ���� 3�� �� �� ���� 0�� ���� ��� ������ �����Ѵ�.
*/

#include <iostream>
#include <time.h>

using namespace std;

int main() {
	srand((unsigned int)time(0));

	int iArray[9] = { 1,2,3,4,5,6,7,8,9 };
	
	// Shuffle
	int temp, idx1, idx2;
	for (int i = 0; i < 100; i++) {
		idx1 = rand() % 9;
		idx2 = rand() % 9;

		temp = iArray[idx1];
		iArray[idx1] = iArray[idx2];
		iArray[idx2] = temp;
	}
	
	// 1~9 ������ ������ ���� 3�� ��� (�׽�Ʈ�� ����)
	/*for (int i = 0; i < 3; i++) {
		cout << iArray[i] << "\t";
	}
	cout << endl << endl;*/


	int num[3];
	int strike = 0;
	int ball = 0;

	while (1) {
		// ����ڰ� ���� 3�� �Է�
		cout << "1~9 ������ ���� 3���� �Է����ּ���: ";
		for (int i = 0; i < 3; i++) {
			cin >> num[i];
			if (num[i] == 0) {
				goto done;
			}
		}

		// strike, ball ã��
		for (int i = 0; i < 3; i++) {
			if (num[i] == iArray[i]) {
				strike++;
			}
			else {
				for (int j = 0; j < 3; j++) {
					if (num[i] == iArray[j]) {
						ball++;
					}
				}
			}
		}

		if (strike == 0 && ball == 0) {
			cout << "Out" << endl;
		}
		else if (strike == 3) {
			cout << "Clear!!!" << endl;
			break;
		}
		else {
			cout << strike << " strike, " << ball << " ball" << endl;
		}

		// �ٽ� �ʱ�ȭ
		strike = 0;
		ball = 0;
	}
	done:

	return 0;
}