// 비트 논리 연산자와 쉬프트 연산자

#include <iostream>

using namespace std;

int main() {

	// 상수 : 변하지 않는 수. 값을 한 번 지정해놓으면 바꿀 수 없다.
	// 상수는 선언과 동시에 값을 지정해두어야 한다.
	const int	iAttack = 0x00000001;	//	   1
	const int	iArmor = 0x00000002;	//	  10
	const int	iHP = 0x00000004;		//	 100
	const int	iMP = 0x00000008;		//	1000
	const int iCritical = 0x00000010;	// 10000

	// 1 | 100 = 001 | 100 = 101
	// 00101 | 10000 = 10101
	int iBuf = iAttack | iHP | iCritical;		// ==> Attack, HP, Critical 버프 생성

	// 연산자 축약형 : 연산자를 줄여서 사용할 수 있다.
	// 아래를 풀어서 쓰면 iBuf = iBuf ^ iHP;
	// 10101 ^ 00100 = 10001
	iBuf ^= iHP;		// ==> HP 버프만 사라진다. (XOR 사용)

	// 10001 ^ 00100 = 10101
	iBuf ^= iHP;		// ==> HP 버프만 생성된다. (XOR를 사용하여 버프 생성/삭제 가능)


	// 10101 & 00001 = 00001 (1)
	cout << "Attack : " << (iBuf & iAttack) << endl;
	// 10101 & 00010 = 0
	cout << "Armor : " << (iBuf & iArmor) << endl;
	cout << "HP : " << (iBuf & iHP) << endl;
	cout << "MP : " << (iBuf & iMP) << endl;
	cout << "Critical : " << (iBuf & iCritical) << endl;

	/*
	쉬프트 연산자 : <<, >> 값 대 값을 연산하여 값으로 나오게 된다.
	이 연산자 또한 이진수 단위의 연산을 하게 된다.
	
	< 빠른 곱셈 >
	20 << 2 = 1010000 (2진수) = 80 (10진수)
	20 << 3 = 10100000 (2진수) = 160 (10진수)
	20 << 4 = 10100000 (2진수) = 320 (10진수)
	20을 2진수로 변환한다.
	1010000
	10100000
	101000000

	< 빠른 나눗셈 >
	20 >> 2 = 5			| 20 / 2^2 = 5
	20 >> 3 = 2			| 20 / 2^3 = 2 (소수점 제외)
	101
	10
	*/

	int iHigh = 187;
	int iLow = 13560;
	
	int iNumber = iHigh;

	// iNumber에는 187이 들어가있다. 이 값을 <- 이 방향으로 16비트 이동시키면
	// 상위 16비트에 값이 들어가게 된다.
	iNumber <<= 16;

	// 하위 16비트를 채운다.
	iNumber |= iLow;

	// High 값을 출력한다.
	cout << "High : " << (iNumber >> 16) << endl;		// iHigh 값만 뽑아올 수 있다.
	cout << "Low : " << (iNumber & 0x0000ffff) << endl;	// iLow 값만 뽑아올 수 있다.


	return 0;
}