// ���������

#include <iostream>

using namespace std;

int main() {

	FILE* pFile = NULL;

	/*
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
		// 3�� ����: �����ϰ����ϴ� ���� ����
		// 4�� ����: ������ ������ ��Ʈ��
		fwrite(pText, 1, 4, pFile);

		fclose(pFile);

		cout << "���� ����� ����" << endl;
	}
	*/
	
	// ���� �б�
	fopen_s(&pFile, "hot.txt", "rt");

	if (pFile) {
		char strText[5] = {};
		fread(strText, 1, 4, pFile);

		cout << strText << endl;

		fclose(pFile);

		cout << "���� �б� ����" << endl;
	}

	return 0;
}