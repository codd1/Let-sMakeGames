// 야구게임

/*
	숙제: 야구게임 만들기
	1~9 사이의 랜덤한 숫자 3개를 얻어온다. 단, 숫자는 중복되면 안된다.
	3개의 숫자는 * * *의 형태로 출력되고 이 3개의 숫자를 맞추는 게임이다.
	사용자는 이 3개의 숫자를 맞출 때까지 계속해서 3개씩 숫자를 입력한다.
	만약 맞춰야할 숫자가 7 3 8일 경우 사용자는 3개의 숫자를 계속 입력한다.
	입력: 1 2 4 를 입력했을 경우, 1 2 4는 맞춰야할 숫자 중 아무 것도 없으므로 Out 을 출력한다.

	입력: 7 5 9를 입력했을 경우 7은 맞춰야할 숫자 중 있고 위치도 같으므로 strike이나, 5 9는 없으므로 출력은 1strike 0ball을 출력한다.

	입력: 7 8 6을 입력했을 경우 7은 맞춰야할 숫자 중 있고 위치도 같으므로 strike이고 8은 숫자는 있지만 위치가 다르므로 1strike 1ball을 출력한다.

	이렇게 출력을 하고 입력을 받으면서 최종적으로 3개의 숫자를 자리까지 모두 알맞게 입력하면 게임이 종료된다.
	만약 입력받은 숫자 3개 중 한 개라도 0이 있을 경우 게임을 종료한다.
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
	
	// 1~9 사이의 랜덤한 숫자 3개 출력 (테스트를 위함)
	/*for (int i = 0; i < 3; i++) {
		cout << iArray[i] << "\t";
	}
	cout << endl << endl;*/


	int num[3];
	int strike = 0;
	int ball = 0;

	while (1) {
		// 사용자가 숫자 3개 입력
		cout << "1~9 사이의 숫자 3개를 입력해주세요: ";
		for (int i = 0; i < 3; i++) {
			cin >> num[i];
			if (num[i] == 0) {
				goto done;
			}
		}

		// strike, ball 찾기
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

		// 다시 초기화
		strike = 0;
		ball = 0;
	}
	done:

	return 0;
}