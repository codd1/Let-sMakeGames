// TextRPG

#include <iostream>
#include <time.h>

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum STORE_MENU {
	SM_NONE,
	SM_WEAPON,
	SM_ARMOR,
	SM_BACK
};

enum BUY {
	BUY_NONE,
	BUY_FIRST,
	BUY_SECOND,
	BUY_THIRD,
	BUY_BACK
};

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

struct _tagItem {
	char strName[NAME_SIZE];
	char strTypeName[NAME_SIZE];
	ITEM_TYPE eType;
	int iMin;
	int iMax;
	int iPrice;
	int iSell;
	char strDesc[ITEM_DESC_LENGTH];		// 아이템 설명
};

struct _tagInventory {
	_tagItem tItem[INVENTORY_MAX];		// 인벤토리 칸수
	int iItemCount;
	int iGold;
};

struct _tagPlayer {
	char strName[NAME_SIZE];
	char strJobName[NAME_SIZE];
	JOB eJob;
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iExp;
	int iLevel;
	_tagInventory tInventory;
	_tagItem tEquip[EQ_MAX];
	bool bEquip[EQ_MAX];
};

struct _tagMonster {
	char strName[NAME_SIZE];
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHP;
	int iHPMax;
	int iMP;
	int iMPMax;
	int iLevel;
	int iExp;		// 몬스터 처치 시 플레이어 획득 경험치
	int iGoldMin;	// 몬스터 처치 시 플레이어 획득 골드
	int iGoldMax;
};

struct _tagLevelUpStatus {
	int iAttackMin;
	int iAttackMax;
	int iArmorMin;
	int iArmorMax;
	int iHPMin;
	int iHPMax;
	int iMPMin;
	int iMPMax;
};

int main() {

	srand((unsigned int)time(0));

	// 레벨업에 필요한 경험치 목록을 만든다.
	const int iLevelUpExp[LEVEL_MAX] = { 4000,10000,20000,35000,50000,70000,100000,150000,200000,400000 };

	// JOB_END == 4.
	// 직업이 3개이므로 -1 해주어서 배열을 각 직업별로 생성하도록 한다.
	_tagLevelUpStatus tLvUpTable[JOB_END - 1] = {};

	tLvUpTable[JOB_KNIGHT - 1].iAttackMin = 4;
	tLvUpTable[JOB_KNIGHT - 1].iAttackMax = 10;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMin = 8;
	tLvUpTable[JOB_KNIGHT - 1].iArmorMax = 16;
	tLvUpTable[JOB_KNIGHT - 1].iHPMin = 50;
	tLvUpTable[JOB_KNIGHT - 1].iHPMax = 100;
	tLvUpTable[JOB_KNIGHT - 1].iMPMin = 10;
	tLvUpTable[JOB_KNIGHT - 1].iMPMax = 20;

	tLvUpTable[JOB_ARCHER - 1].iAttackMin = 10;
	tLvUpTable[JOB_ARCHER - 1].iAttackMax = 15;
	tLvUpTable[JOB_ARCHER - 1].iArmorMin = 5;
	tLvUpTable[JOB_ARCHER - 1].iArmorMax = 10;
	tLvUpTable[JOB_ARCHER - 1].iHPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iHPMax = 60;
	tLvUpTable[JOB_ARCHER - 1].iMPMin = 30;
	tLvUpTable[JOB_ARCHER - 1].iMPMax = 50;

	tLvUpTable[JOB_WIZARD - 1].iAttackMin = 15;
	tLvUpTable[JOB_WIZARD - 1].iAttackMax = 20;
	tLvUpTable[JOB_WIZARD - 1].iArmorMin = 3;
	tLvUpTable[JOB_WIZARD - 1].iArmorMax = 7;
	tLvUpTable[JOB_WIZARD - 1].iHPMin = 20;
	tLvUpTable[JOB_WIZARD - 1].iHPMax = 40;
	tLvUpTable[JOB_WIZARD - 1].iMPMin = 50;
	tLvUpTable[JOB_WIZARD - 1].iMPMax = 100;

	// 게임을 시작할 때 플레이어 정보를 설정한다.
	_tagPlayer tPlayer = {};

	cout << "이름: ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요: ";
		cin >> iJob;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		else if (iJob != JOB_KNIGHT && iJob != JOB_ARCHER && iJob != JOB_WIZARD) {
			iJob = JOB_NONE;
		}
	}

	// 초기 플레이어 정보
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob) {
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "기사");
		tPlayer.iAttackMin = 5;
		tPlayer.iAttackMax = 10;
		tPlayer.iArmorMin = 15;
		tPlayer.iArmorMax = 20;
		tPlayer.iHP = 500;
		tPlayer.iHPMax = 500;
		tPlayer.iMP = 100;
		tPlayer.iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(tPlayer.strJobName, "궁수");
		tPlayer.iAttackMin = 10;
		tPlayer.iAttackMax = 15;
		tPlayer.iArmorMin = 10;
		tPlayer.iArmorMax = 15;
		tPlayer.iHP = 400;
		tPlayer.iHPMax = 400;
		tPlayer.iMP = 200;
		tPlayer.iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(tPlayer.strJobName, "마법사");
		tPlayer.iAttackMin = 15;
		tPlayer.iAttackMax = 20;
		tPlayer.iArmorMin = 5;
		tPlayer.iArmorMax = 10;
		tPlayer.iHP = 300;
		tPlayer.iHPMax = 300;
		tPlayer.iMP = 300;
		tPlayer.iMPMax = 300;
		break;
	}

	// 몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// 고블린 생성
	strcpy_s(tMonsterArr[0].strName, "고블린");
	tMonsterArr[0].iAttackMin = 20;
	tMonsterArr[0].iAttackMax = 30;
	tMonsterArr[0].iArmorMin = 2;
	tMonsterArr[0].iArmorMax = 5;
	tMonsterArr[0].iHP = 100;
	tMonsterArr[0].iHPMax = 100;
	tMonsterArr[0].iMP = 10;
	tMonsterArr[0].iMPMax = 10;
	tMonsterArr[0].iLevel = 1;
	tMonsterArr[0].iExp = 1000;
	tMonsterArr[0].iGoldMin = 500;
	tMonsterArr[0].iGoldMax = 1500;

	// 트롤 생성
	strcpy_s(tMonsterArr[1].strName, "트롤");
	tMonsterArr[1].iAttackMin = 80;
	tMonsterArr[1].iAttackMax = 130;
	tMonsterArr[1].iArmorMin = 60;
	tMonsterArr[1].iArmorMax = 90;
	tMonsterArr[1].iHP = 2000;
	tMonsterArr[1].iHPMax = 2000;
	tMonsterArr[1].iMP = 100;
	tMonsterArr[1].iMPMax = 100;
	tMonsterArr[1].iLevel = 5;
	tMonsterArr[1].iExp = 7000;
	tMonsterArr[1].iGoldMin = 6000;
	tMonsterArr[1].iGoldMax = 8000;

	// 드래곤 생성
	strcpy_s(tMonsterArr[2].strName, "드래곤");
	tMonsterArr[2].iAttackMin = 250;
	tMonsterArr[2].iAttackMax = 500;
	tMonsterArr[2].iArmorMin = 200;
	tMonsterArr[2].iArmorMax = 400;
	tMonsterArr[2].iHP = 30000;
	tMonsterArr[2].iHPMax = 30000;
	tMonsterArr[2].iMP = 20000;
	tMonsterArr[2].iMPMax = 20000;
	tMonsterArr[2].iLevel = 10;
	tMonsterArr[2].iExp = 30000;
	tMonsterArr[2].iGoldMin = 20000;
	tMonsterArr[2].iGoldMax = 50000;


	// 상점에서 판매할 아이템 목록을 생성한다.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

	// 무기 - 녹슨 무기 생성
	strcpy_s(tStoreWeapon[0].strName, "녹슨 무기");
	strcpy_s(tStoreWeapon[0].strTypeName, "무기");
	tStoreWeapon[0].iMin = 30;
	tStoreWeapon[0].iMax = 50;
	tStoreWeapon[0].iPrice = 5000;
	tStoreWeapon[0].iSell = tStoreWeapon[0].iPrice * 0.7f;
	tStoreWeapon[0].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[0].strDesc, "언제 부서질지 모르는 녹슨 무기이다.");

	// 무기 - 일반 무기 생성
	strcpy_s(tStoreWeapon[1].strName, "일반 무기");
	strcpy_s(tStoreWeapon[1].strTypeName, "무기");
	tStoreWeapon[1].iMin = 400;
	tStoreWeapon[1].iMax = 500;
	tStoreWeapon[1].iPrice = 12000;
	tStoreWeapon[1].iSell = tStoreWeapon[1].iPrice * 0.7f;
	tStoreWeapon[1].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[1].strDesc, "평범한 무기이지만 꽤 쓸만해보인다.");

	// 무기 - 스페셜 무기 생성
	strcpy_s(tStoreWeapon[2].strName, "스페셜 무기");
	strcpy_s(tStoreWeapon[2].strTypeName, "무기");
	tStoreWeapon[2].iMin = 1200;
	tStoreWeapon[2].iMax = 1500;
	tStoreWeapon[2].iPrice = 20000;
	tStoreWeapon[2].iSell = tStoreWeapon[2].iPrice * 0.7f;
	tStoreWeapon[2].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[2].strDesc, "이 세계에서 가장 강력한 스페셜 무기이다. 소문에 의하면 엑스칼리버라고도 불린다.");


	// 방어구 - 낡은 방어구 생성
	strcpy_s(tStoreArmor[0].strName, "낡은 방어구");
	strcpy_s(tStoreArmor[0].strTypeName, "방어구");
	tStoreArmor[0].iMin = 30;
	tStoreArmor[0].iMax = 50;
	tStoreArmor[0].iPrice = 5000;
	tStoreArmor[0].iSell = tStoreArmor[0].iPrice * 0.7f;
	tStoreArmor[0].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[0].strDesc, "많이 헤진 낡은 방어구이다.");

	// 방어구 - 괜찮은 방어구 생성
	strcpy_s(tStoreArmor[1].strName, "괜찮은 방어구");
	strcpy_s(tStoreArmor[1].strTypeName, "방어구");
	tStoreArmor[1].iMin = 200;
	tStoreArmor[1].iMax = 300;
	tStoreArmor[1].iPrice = 12000;
	tStoreArmor[1].iSell = tStoreArmor[1].iPrice * 0.7f;
	tStoreArmor[1].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[1].strDesc, "평범해보이는 쓸만한 괜찮은 방어구이다.");

	// 방어구 - 스페셜 방어구 생성
	strcpy_s(tStoreArmor[2].strName, "스페셜 방어구");
	strcpy_s(tStoreArmor[2].strTypeName, "방어구");
	tStoreArmor[2].iMin = 800;
	tStoreArmor[2].iMax = 1000;
	tStoreArmor[2].iPrice = 20000;
	tStoreArmor[2].iSell = tStoreArmor[2].iPrice * 0.7f;
	tStoreArmor[2].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[2].strDesc, "이 세계에서 가장 강력한 스페셜 방어구이다. 전설에 의하면 아직까지 이 방어구를 뚫은 자는 아무도 없다고 한다.");


	while (true) {
		system("cls");
		cout << "===================== 로비 =====================" << endl;
		cout << "1. 맵" << endl;
		cout << "2. 상점" << endl;
		cout << "3. 인벤토리" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요: ";

		int iMenu;
		cin >> iMenu;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT) {
			break;
		}

		switch (iMenu) {
		case MM_MAP:
			while (true) {
				system("cls");
				cout << "===================== 맵 =====================" << endl;
				cout << "1. 쉬움" << endl;
				cout << "2. 보통" << endl;
				cout << "3. 어려움" << endl;
				cout << "4. 뒤로가기" << endl;
				cout << "맵을 선택하세요: ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (iMenu == MT_BACK) {
					break;
				}

				// 선택한 메뉴 -1은 몬스터 배열의 인덱스가 된다.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true) {
					system("cls");

					switch (iMenu) {
					case MT_EASY:
						cout << "===================== 쉬움 =====================" << endl;
						break;
					case MT_NORMAL:
						cout << "===================== 보통 =====================" << endl;
						break;
					case MT_HARD:
						cout << "===================== 어려움 =====================" << endl;
						break;
					}

					// 플레이어 정보를 출력한다.
					cout << "===================== Player =====================" << endl;
					cout << "이름: " << tPlayer.strName << "\t직업: " << tPlayer.strJobName << endl;
					cout << "레벨: " << tPlayer.iLevel << "\t경험치: " << tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

					// 무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다.
					if (tPlayer.bEquip[EQ_WEAPON] == true) {
						cout << "공격력: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " - " << tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else {
						cout << "공격력: " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax;
					}

					// 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
					if (tPlayer.bEquip[EQ_ARMOR] == true) {
						cout << "\t방어력: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " - " << tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}
					else {
						cout << "\t방어력: " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;
					}

					cout << "체력: " << tPlayer.iHP << " / " << tPlayer.iHPMax << "\t마나: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON]) {
						cout << "장착무기: " << tPlayer.tEquip[EQ_WEAPON].strName;
					}
					else {
						cout << "장착무기: 없음";
					}

					if (tPlayer.bEquip[EQ_ARMOR]) {
						cout << "\t장착방어구: " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
					}
					else {
						cout << "\t장착방어구: 없음" << endl;
					}

					cout << "보유골드: " << tPlayer.tInventory.iGold << " Gold" << endl;

					// 몬스터 정보 출력
					cout << "===================== Monster =====================" << endl;
					cout << "이름: " << tMonster.strName << "\t레벨: " << tMonster.iLevel << endl;
					cout << "공격력: " << tMonster.iAttackMin << " - " << tMonster.iAttackMax << "\t방어력: " << tMonster.iArmorMin << " - " << tMonster.iArmorMax << endl;
					cout << "체력: " << tMonster.iHP << " / " << tMonster.iHPMax << "\t마나: " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
					cout << "획득 경험치: " << tMonster.iExp << "\t획득 골드: " << tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					cout << "1. 공격" << endl;
					cout << "2. 도망가기" << endl << endl;
					cout << "메뉴를 선택하세요: ";
					cin >> iMenu;
					cout << endl;

					if (cin.fail()) {
						cin.clear();
						cin.ignore(1024, '\n');
						continue;
					}
					else if (iMenu == BATTLE_BACK) {
						break;
					}
					switch (iMenu) {
					case BATTLE_ATTACK:
					{
						// 예를 들어 Min 5 Max 15 라고 가정할 경우
						// 15-5+1을 하면 11이 된다. 11로 나눈 나머지는 0~10이 나오게 되고
						// 여기에 Min값인 5를 더하게 되면 5~15 사이로 값이 나오게 된다.

						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						// 무기를 장착하고 있을 경우 무기와 Min, Max를 더해준다.
						if (tPlayer.bEquip[EQ_WEAPON]) {
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) + tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						// 삼항연산자의 형태 -> 조건식 ? ture일 때 값 : false일 때 값 : 
						iDamage = iDamage < 1 ? 1 : iDamage;	// 최소 데미지값을 1로 한다.

						// 몬스터 HP를 감소시킨다.
						tMonster.iHP -= iDamage;

						cout << tPlayer.strName << "가 " << tMonster.strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;

						// 몬스터가 죽었을 경우를 처리한다.
						if (tMonster.iHP <= 0) {
							cout << tMonster.strName << " 몬스터가 사망했습니다." << endl;

							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << " 경험치를 획득했습니다." << endl;
							cout << iGold << " Gold를 획득했습니다." << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;

							// 레벨업을 했는지 체크한다.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1]) {
								// 플레이어 경험치를 레벨업에 필요한 경험치만큼 차감한다.
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

								// 레벨을 증가시킨다.
								tPlayer.iLevel++;

								cout << "레벨업 했습니다!" << endl;

								// 능력치를 상승시킨다.
								int iJobIndex = tPlayer.eJob - 1;	// 직업 인덱스
								int iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) + tLvUpTable[iJobIndex].iHPMin;
								int iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) + tLvUpTable[iJobIndex].iMPMin;

								tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

								tPlayer.iHPMax += iHPUp;
								tPlayer.iMPMax += iMPUp;

								// 체력과 마나를 회복시킨다.
								tPlayer.iHP = tPlayer.iHPMax;
								tPlayer.iMP = tPlayer.iMPMax;

							}

							system("pause");
							break;
						}

						// 몬스터가 살아있다면 플레이어를 공격한다.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) + tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR]) {
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

						iDamage = iAttack - iArmor;
						iDamage = iDamage < 1 ? 1 : iDamage;	// 최소 데미지값을 1로 한다.

						// 플레이어의 HP를 감소시킨다.
						tPlayer.iHP -= iDamage;

						cout << tMonster.strName << "가 " << tPlayer.strName << "에게 " << iDamage << " 피해를 입혔습니다." << endl;

						// 플레이어가 죽었을 경우
						if (tPlayer.iHP <= 0) {
							cout << tPlayer.strName << " 플레이어가 사망했습니다." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " 경험치를 잃었습니다." << endl;
							cout << iGold << " Gold를 잃었습니다." << endl;

							// 플레이어의 HP와 MP를 회복한다.
							tPlayer.iHP = tPlayer.iHPMax;
							tPlayer.iMP = tPlayer.iMPMax;
						}
						cout << endl;
						system("pause");

						break;
					}
					case BATTLE_BACK:
						break;
					}
				}

			}
			break;
		case MM_STORE:
			while (true) {
				system("cls");
				cout << "===================== 상점 =====================" << endl;
				cout << "1. 무기상점" << endl;
				cout << "2. 방어구상점" << endl;
				cout << "3. 뒤로가기" << endl;
				cout << "상점을 선택하세요: ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == SM_BACK) {
					break;
				}

				switch (iMenu) {
				case SM_WEAPON:
					while (true) {
						system("cls");
						cout << "===================== 무기상점 =====================" << endl;
						// 판매 목록을 보여준다.
						for (int i = 0; i < STORE_WEAPON_MAX; i++) {
							cout << "===================== " << i + 1 << ". " << tStoreWeapon[i].strName << " =====================" << endl;
							cout << "아이템 타입 : " << tStoreWeapon[i].strTypeName << endl;
							cout << "능력치: " << tStoreWeapon[i].iMin << " - " << tStoreWeapon[i].iMax << endl;
							cout << "구매가격: " << tStoreWeapon[i].iPrice << " Gold\t판매가격: " << tStoreWeapon[i].iSell << " Gold" << endl;
							cout << "아이템 설명: " << tStoreWeapon[i].strDesc << endl << endl;
						}
						cout << "===================== 4. 뒤로가기 =====================" << endl << endl;
						cout << "현재 보유 Gold: " << tPlayer.tInventory.iGold << " Gold" << endl;
						cout << "메뉴를 선택하세요: ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == BUY_BACK) {
							break;
						}

						switch (iMenu) {
						case BUY_FIRST:
							if (tPlayer.tInventory.iGold < tStoreWeapon[0].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreWeapon[0].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[0].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreWeapon[0].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreWeapon[0].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreWeapon[0].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreWeapon[0].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreWeapon[0].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreWeapon[0].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreWeapon[0].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreWeapon[0].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						case BUY_SECOND:
							if (tPlayer.tInventory.iGold < tStoreWeapon[1].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreWeapon[1].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[1].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreWeapon[1].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreWeapon[1].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreWeapon[1].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreWeapon[1].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreWeapon[1].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreWeapon[1].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreWeapon[1].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreWeapon[1].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						case BUY_THIRD:
							if (tPlayer.tInventory.iGold < tStoreWeapon[2].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreWeapon[2].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[2].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreWeapon[2].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreWeapon[2].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreWeapon[2].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreWeapon[2].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreWeapon[2].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreWeapon[2].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreWeapon[2].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreWeapon[2].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						}
						system("pause");
					}
					break;

				case SM_ARMOR:
					while (true) {
						system("cls");
						cout << "===================== 방어구 상점 =====================" << endl;
						// 판매 목록을 보여준다.
						for (int i = 0; i < STORE_ARMOR_MAX; i++) {
							cout << "===================== " << i + 1 << ". " << tStoreArmor[i].strName << " =====================" << endl;
							cout << "아이템 타입 : " << tStoreArmor[i].strTypeName << endl;
							cout << "능력치: " << tStoreArmor[i].iMin << " - " << tStoreArmor[i].iMax << endl;
							cout << "구매가격: " << tStoreArmor[i].iPrice << " Gold\t판매가격: " << tStoreArmor[i].iSell << " Gold" << endl;
							cout << "아이템 설명: " << tStoreArmor[i].strDesc << endl << endl;
						}
						cout << "===================== 4. 뒤로가기 =====================" << endl << endl;
						cout << "메뉴를 선택하세요: ";
						cin >> iMenu;

						if (cin.fail()) {
							cin.clear();
							cin.ignore(1024, '\n');
							continue;
						}
						else if (iMenu == BUY_BACK) {
							break;
						}

						switch (iMenu) {
						case BUY_FIRST:
							if (tPlayer.tInventory.iGold < tStoreArmor[0].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreArmor[0].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[0].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreArmor[0].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreArmor[0].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreArmor[0].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreArmor[0].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreArmor[0].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreArmor[0].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreArmor[0].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreArmor[0].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						case BUY_SECOND:
							if (tPlayer.tInventory.iGold < tStoreArmor[1].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreArmor[1].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[1].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreArmor[1].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreArmor[1].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreArmor[1].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreArmor[1].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreArmor[1].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreArmor[1].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreArmor[1].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreArmor[1].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						case BUY_THIRD:
							if (tPlayer.tInventory.iGold < tStoreArmor[2].iPrice) {
								cout << "구매 불가: 잔액이 부족합니다." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "구매 불가: 인벤토리 공간이 부족합니다." << endl;
							}
							else {
								cout << "구매 성공: " << tStoreArmor[2].strName << " 아이템을 구매했습니다." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[2].iPrice;
								cout << "잔액: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// 인벤토리에 아이템 추가
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strName, tStoreArmor[2].strName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strTypeName, tStoreArmor[2].strTypeName);
								strcpy_s(tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].strDesc, tStoreArmor[2].strDesc);
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iPrice = tStoreArmor[2].iPrice;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iSell = tStoreArmor[2].iSell;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMax = tStoreArmor[2].iMax;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].iMin = tStoreArmor[2].iMin;
								tPlayer.tInventory.tItem[tPlayer.tInventory.iItemCount].eType = tStoreArmor[2].eType;

								tPlayer.tInventory.iItemCount++;
							}
							break;
						}
						system("pause");
					}
					break;
				}
			}
			break;

		case MM_INVENTORY:
			while (true) {
				system("cls");
				cout << "===================== 인벤토리 =====================" << endl;
				for (int i = 0; i < tPlayer.tInventory.iItemCount; i++) {
					cout << i + 1 << ". 이름: " << tPlayer.tInventory.tItem[i].strName << endl;
					cout << "아이템 타입 : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "능력치: " << tPlayer.tInventory.tItem[i].iMin << " - " << tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "구매가격: " << tPlayer.tInventory.tItem[i].iPrice << " Gold\t판매가격: " << tPlayer.tInventory.tItem[i].iSell << " Gold" << endl;
					cout << "아이템 설명: " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}
				cout << endl << "총 아이템 갯수: " << tPlayer.tInventory.iItemCount << endl << endl;

				cout << tPlayer.tInventory.iItemCount + 1 << ". 뒤로가기" << endl;
				cout << "장착할 아이템을 선택하세요: ";

				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}
				else if (iMenu == tPlayer.tInventory.iItemCount + 1) {
					break;
				}
				else if (iMenu < 1 || iMenu > tPlayer.tInventory.iItemCount + 1) {
					cout << "잘못 선택했습니다." << endl;
					system("pause");
					continue;
				}

				// 아이템 인덱스를 구해준다.
				int idx = iMenu - 1;

				// 제대로 선택했을 경우 해당 아이템의 종류에 따라 장착 부위를 결정한다.
				EQUIP eq;

				switch (tPlayer.tInventory.tItem[idx].eType) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// 아이템이 장착되어 있을 경우 장착 되어있는 아이템과 장착할 아이템을 교체해준다. (Swap)
				if (tPlayer.bEquip[eq] == true) {
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				// 장착되어있지 않을 경우 인벤토리 아이템을 장착창으로 옮기고 인벤토리는 1칸 비워지게된다.
				else {
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++) {
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					tPlayer.tInventory.iItemCount--;

					// 장착했으므로 true로 변경
					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << " 아이템을 장착했습니다." << endl;
				system("pause");
			}
			break;
		default:
			cout << "잘못 선택했습니다." << endl;
			break;
		}


	}


	return 0;
}