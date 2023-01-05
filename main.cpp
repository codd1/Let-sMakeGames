// #include: 헤더파일을 여기에 포함시키는 기능이다.
#include <iostream>

using namespace std;		// std:: 제거 가능

// 실행 과정: 컴파일 -> 빌드 -> 실행
// 컴파일: 번역 작업
// Ctrl + Shift + B를 이용해서 컴파일 및 빌드를 할 수 있다.

// C++의 시작점은 main 함수이다. main함수는 반드시 있어야 한다.
int main() {

	// C++ 표준 기능의 대부분은 std 라는 namespace 안에 존재하고 있다. 이름이 겹치는 것을
	// 방지해주기 위해서이다.
	// cout: 콘솔창에 출력해주는 기능이다. 뒤에 있는 ""(큰따옴표) 안에 있는 문자들을
	// 화면에 출력해준다. 문자 여러개를 사용할때는 반드시 "" 안에 넣어주고 이런 것을
	// 문자열 이라고 한다.
	// endl: 개행기능

	std::cout << "Test Output" << std::endl;
	
	cout << "std namespace 사용" << endl;

	/*
	변수
	용량의 최소 단위: bit
	1byte = 8bit
	1kbyte = 1024byte
	1mbyte = 1024kbyte
	1gbyte = 1024mbyte
	1tbyte = 1024gbyte
	문자를 표현하는 방법: ASCII 코드 표를 가지고 있다.
	false : 0
	true : 0이 아닌 모든 수
	종류	|	용량	|	데이터	|	표현 범위		|
	char	|	1byte	|	문자	|	-128 ~ 127		|
	bool	|	1byte	|	참/거짓	|	ture / false	|
	short	|	2byte	|	정수	|	-32768 ~ 32767	|
	int		|	4byte	|	정수	|	약 -22억 ~ 21억	|
	float	|	4byte	|	실수	|
	double	|	8byte	|	실수	|
	*/

	int Number = 10;
	Number = 20;
	
	cout << Number << endl;

	bool bTest = true;
	bTest = false;

	cout << bTest << endl;

	// 영문이나 숫자는 1byte를 차지한다. 하지만 한글이나 한문, 등의 문자들은 2byte를
	// 차지하기 때문에 char 변수 하나에 저장하기가 힘들다.

	char cTest = 't';

	cout << cTest << endl;

	// float에서는 실수 뒤에 f를 붙여줘야함. (float형 실수)
	float fNumber = 3.14f;

	cout << fNumber << endl;

	// double에서는 실수 뒤에 붙이지 않음. (double형 실수)
	double dNumber = 123.4567;

	cout << dNumber << endl;

	return 0;
}