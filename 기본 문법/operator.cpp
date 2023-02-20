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
		// ���� ����. �̷��� ���� ��� this�� �ڱ��ڽ��� �������̰� *�� �ٿ��� �ڱ��ڽ��� �������Ͽ� ��� �����͸� �����ϰ��Ѵ�.
		*this = pt;
	}

	_tagPoint operator +(const _tagPoint& pt) {
		_tagPoint result;
		// x, y: main �Լ����� pt1�� x, y�� = 10, 20
		// pt.x, pt.y: main �Լ����� pt2�� x, y�� = 30, 40
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

	// POINT ����ü�� +�����ڰ� operator�� ������ �Ǿ��ִ�.
	// �׷��� ���ϱ� ������ �����ϰԵǰ� pt1�� +������ �Լ��� ȣ�����ִ� �����̴�. pt2�� ���ڷ� �Ѱ��ش�.
	pt3 = pt1 + pt2;

	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	// << ������
	pt3 << pt1;
	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	// >> ������
	pt3 >> pt1;
	cout << "x: " << pt3.x << "\ty: " << pt3.y << endl;

	return 0;
}