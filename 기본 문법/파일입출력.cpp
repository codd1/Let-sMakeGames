// 파일입출력

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

	// 1번 인자: 파일의 이중포인터.
	// 2번 인자: 파일 경로. (파일이 생성되는 기준 경로는 현재 프로젝트가 있는 폴더 기준이다.
	// 만약 실행파일(.exe)로 실행했을 경우에는 해당 exe파일이 있는 경로 기준으로 생성해준다.
	// 3번 인자: 파일 모드
	// 파일 읽기, 쓰기, 접근
	// 파일 형태 - 텍스트 파일, 바이너리 파일
	// r: 읽기 / w: 쓰기 / a: 접근		t: 텍스트파일, b: 바이너리 파일
	fopen_s(&pFile, "hot.txt", "wt");

	if (pFile != NULL) {	// 만들기 성공했을 경우
		// fwrite, fread 2개의 함수가 제공된다. (+fputs, fgets)
		const char* pText = "abcd";
		// 1번 인자: 저장하고자하는 값의 메모리 주소
		// 2번 인자: 저장하고자하는 값의 변수타입의 메모리 크기
		fwrite(pText, 1, 4, pFile);

		fclose(pFile);

		cout << "파일 만들기 성공" << endl;
	}


	return 0;
}