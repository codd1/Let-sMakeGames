// operator

#include <iostream>

using namespace std;

typedef struct _tagPoint {
	int x;
	int y;

	_tagPoint() :
		x(0),
		y(0) {

	}

	_tagPoint(int _x, int _y) :
		x(_x),
		y(_y) {

	}

	_tagPoint(const _tagPoint& pt) {
		// 얕은 복사. 이렇게 해줄 경우 this는 자기자신의 포인터이고 *을 붙여서 자기자신을 역참조하여 모든 데이터를 복사하게한다.
		*this = pt;
	}

	_tagPoint operator +(const _tagPoint& pt) {
		_tagPoint result;
		// x, y: main 함수에서 pt1의 x, y값 = 10, 20
		// pt.x, pt.y: main 함수에서 pt2의 x, y값 = 30, 40
		result.x = x + pt.x;
		result.y = y + pt.y;

		return result;
	}

	void operator << (const _tagPoint& pt) {
		x = pt.x;
		y = pt.y;
	}

	void operator >> (const _tagPoint& pt) {
		x = pt.y;
		y = pt.x;
	}

} POINT, *PPOINT;

int main() {

	POINT pt1(10, 20), pt2(30, 40), pt3;

	// POINT 구조체는 +연산자가 operator로 재정의 되어있다.
	// 그래서 더하기 연산이 가능하게되고 pt1의 +연산자 함수를 호출해주는 개념이다. pt2를 인자로 넘겨준다.
	pt3 = pt1 + pt2;

	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	// << 연산자
	pt3 << pt1;
	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	// >> 연산자
	pt3 >> pt1;
	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	return 0;
}