// ���������

#include <iostream>

using namespace std;

void Test(int** pp) {
	*pp = new int;
}

int main() {

	//int* p = NULL;
	//p = new int;
	//Test(&p);

	FILE* pFile = NULL;

	// 1�� ����: ������ ����������.
	// 2�� ����: ���� ���. (������ �����Ǵ� ���� ��δ� ���� ������Ʈ�� �ִ� ���� �����̴�.
	// ���� ��������(.exe)�� �������� ��쿡�� �ش� exe������ �ִ� ��� �������� �������ش�.
	// 3�� ����: ���� ���
	// ���� �б�, ����, ����
	// ���� ���� - �ؽ�Ʈ ����, ���̳ʸ� ����
	// r: �б� / w: ���� / a: ����		t: �ؽ�Ʈ����, b: ���̳ʸ� ����
	fopen_s(&pFile, "hot.txt", "wt");

	if (pFile != NULL) {	// ����� �������� ���
		// fwrite, fread 2���� �Լ��� �����ȴ�. (+fputs, fgets)
		const char* pText = "abcd";
		// 1�� ����: �����ϰ����ϴ� ���� �޸� �ּ�
		// 2�� ����: �����ϰ����ϴ� ���� ����Ÿ���� �޸� ũ��
		fwrite(pText, 1, 4, pFile);

		fclose(pFile);

		cout << "���� ����� ����" << endl;
	}


	return 0;
}