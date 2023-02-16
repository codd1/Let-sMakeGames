// 바이너리 파일

#include <iostream>

using namespace std;

#define NAME_SIZE 32
#define STUDENT_MAX 3

typedef struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
}STUDENT, *PSTUDENT;

int main() {

	STUDENT tStudent[STUDENT_MAX] = {};

	for (int i = 0; i < STUDENT_MAX; i++) {
		cout << "이름: ";
		cin >> tStudent[i].strName;

		tStudent[i].iNumber = i + 1;

		cout << "국어: ";
		cin >> tStudent[i].iKor;

		cout << "영어: ";
		cin >> tStudent[i].iEng;

		cout << "수학: ";
		cin >> tStudent[i].iMath;

		tStudent[i].iTotal = tStudent[i].iKor + tStudent[i].iEng + tStudent[i].iMath;
		tStudent[i].fAvg = tStudent[i].iTotal / STUDENT_MAX;
		
		cout << endl;
	}

	// 학생 정보를 파일에 저장한다.
	int iStudentCount = STUDENT_MAX;

	FILE* pFile = NULL;

	fopen_s(&pFile, "Student.std", "wb");

	if (pFile) {
		// 학생 수를 저장한다.
		fwrite(&iStudentCount, 4, 1, pFile);

		for (int i = 0; i < iStudentCount; i++) {
			// 학생 구조체를 통으로 저장한다.
			fwrite(&tStudent[i], sizeof(STUDENT), 1, pFile);
		}

		fclose(pFile);
	}

	return 0;
}