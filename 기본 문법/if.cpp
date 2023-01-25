// if��

#include <iostream>

using namespace std;

int main() {
	const int	iAttack = 0x00000001;	//	   1
	const int	iArmor = 0x00000002;	//	  10
	const int	iHP = 0x00000004;		//	 100
	const int	iMP = 0x00000008;		//	1000
	const int iCritical = 0x00000010;	// 10000

	int iBuf = iAttack | iHP | iCritical;

	/*
		�б⹮���� ũ�� 2���� ������ �ִ�. if��, switch���� �����Ѵ�.
		if��: ������ üũ���ִ� ����̴�.
		����: if(���ǽ�) {} (�ڵ��)
		if���� ���ǽ��� true�� �� ��� �ڵ�� ���� �ڵ尡 ���۵ȴ�.
		false�� ��쿡�� ���۵��� �ʴ´�.
	*/

	if (false) {
		cout << "if�� ������ true�Դϴ�." << endl;
	}

	// ������ �ִ��� Ȯ���Ѵ�.
	// if�� �Ʒ��� �� �ڵ尡 1���� ��� {}(�ڵ��)�� ������ �� �ִ�.
	if ((iBuf & iAttack) != 0) {
		cout << "Attack ������ �ֽ��ϴ�." << endl;
	}
	if ((iBuf & iArmor) != 0)
		cout << "Armor ������ �ֽ��ϴ�." << endl;
	if ((iBuf & iHP) != 0)
		cout << "HP ������ �ֽ��ϴ�." << endl;
	if ((iBuf & iMP) != 0)
		cout << "MP ������ �ֽ��ϴ�." << endl;
	if ((iBuf & iCritical) != 0)
		cout << "Critical ������ �ֽ��ϴ�." << endl;

	// if else��
	if (false)
		cout << "if�� ������ true�Դϴ�." << endl;
	else
		cout << "if�� ������ false�Դϴ�." << endl;


	int iNumber;
	cout << "���ڸ� �Է��ϼ��� : ";
	cin >> iNumber;

	if (10 <= iNumber && iNumber <= 20)
		cout << "10 ~ 20 ������ �����Դϴ�." << endl;
	else if (21 <= iNumber && iNumber <= 30)
		cout << "21 ~ 30 ������ �����Դϴ�." << endl;
	else
		cout << "�� ���� �����Դϴ�. " << endl;

	
	return 0;
}