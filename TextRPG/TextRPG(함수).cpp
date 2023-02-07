// TextRPG 함수 이용해 정리하기

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

enum ITEM_TYPE {
	IT_NONE,
	IT_WEAPON,
	IT_ARMOR,
	IT_BACK
};

enum EQUIP {
	EQ_WEAPON,
	EQ_ARMOR,
	EQ_MAX
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

#define NAME_SIZE			32
#define ITEM_DESC_LENGTH	512
#define INVENTORY_MAX		20
#define STORE_WEAPON_MAX	3
#define STORE_ARMOR_MAX		3
#define LEVEL_MAX			10

// 레벨업에 필요한 경험치 목록을 만든다.
const int g_iLevelUpExp[LEVEL_MAX] = { 4000,10000,20000,35000,50000,70000,100000,150000,200000,400000 };

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

int InputInt();
int OutputMainMenu();
void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu);
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr);
void SetPlayer(_tagPlayer* pPlayer);
int SelectJob();
_tagMonster CreateMonster(const char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax);
void SetMonster(_tagMonster* pMonsterArr);
void OutputBattleTag(int iMenu);
void OutputMonster(_tagMonster* pMonster);
void OutputPlayer(_tagPlayer* pPlayer);
int OutputBattleMenu();

int main() {

	srand((unsigned int)time(0));

	// 게임을 시작할 때 플레이어 정보를 설정한다.
	_tagPlayer tPlayer = {};

	// 플레이어의 정보를 정의한다.
	SetPlayer(&tPlayer);

	// 몬스터를 생성한다.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};
	SetMonster(tMonsterArr);

	bool bLoop = true;

	while (bLoop) {
		switch (OutputMainMenu()) {
		case MM_MAP:
			RunMap(&tPlayer, tMonsterArr);		// 맵 관련 루프를 처리한다.
			break;
		case MM_STORE:
			break;
		case MM_INVENTORY:
			break;
		case MM_EXIT:
			bLoop = false;
			break;
		}
	}

	return 0;
}

// 메인 메뉴를 화면에 보여주고 입력 받은 메뉴를 리턴한다.
// 입력 오류일 경우(잘못된 번호 입력) MM_NONE을 리턴한다. 
int OutputMainMenu() {
	system("cls");
	cout << "===================== 로비 =====================" << endl;
	cout << "1. 맵" << endl;
	cout << "2. 상점" << endl;
	cout << "3. 인벤토리" << endl;
	cout << "4. 종료" << endl;
	cout << "메뉴를 선택하세요: ";

	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MM_NONE || iMenu > MM_EXIT) {
		return MM_NONE;
	}

	return iMenu;
}

// 숫자 입력을 받는다. 입력 오류까지 출력해주고 INT_MAX를 리턴하면 입력 오류 발생
int InputInt() {
	int iInput;
	cin >> iInput;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1024, '\n');
		return INT_MAX;		// INT_MAX가 리턴되면 입력이 잘못됐다는 의미
	}

	return iInput;
}

void OutputBattleTag(int iMenu) {
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
}

void OutputPlayer(_tagPlayer* pPlayer) {
	cout << "===================== Player =====================" << endl;
	cout << "이름: " << pPlayer->strName << "\t직업: " << pPlayer->strJobName << endl;
	cout << "레벨: " << pPlayer->iLevel << "\t경험치: " << pPlayer->iExp << " / " << g_iLevelUpExp[pPlayer->iLevel - 1] << endl;

	// 무기를 장착하고 있을 경우 공격력에 무기공격력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_WEAPON] == true) {
		cout << "공격력: " << pPlayer->iAttackMin << " + " << pPlayer->tEquip[EQ_WEAPON].iMin << " - " << pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_WEAPON].iMax;
	}
	else {
		cout << "공격력: " << pPlayer->iAttackMin << " - " << pPlayer->iAttackMax;
	}

	// 방어구를 장착하고 있을 경우 방어력에 방어구 방어력을 추가하여 출력한다.
	if (pPlayer->bEquip[EQ_ARMOR] == true) {
		cout << "\t방어력: " << pPlayer->iAttackMin << " + " << pPlayer->tEquip[EQ_ARMOR].iMin << " - " << pPlayer->iAttackMax << " + " << pPlayer->tEquip[EQ_ARMOR].iMax << endl;
	}
	else {
		cout << "\t방어력: " << pPlayer->iArmorMin << " - " << pPlayer->iArmorMax << endl;
	}

	cout << "체력: " << pPlayer->iHP << " / " << pPlayer->iHPMax << "\t마나: " << pPlayer->iMP << " / " << pPlayer->iMPMax << endl;

	if (pPlayer->bEquip[EQ_WEAPON]) {
		cout << "장착무기: " << pPlayer->tEquip[EQ_WEAPON].strName;
	}
	else {
		cout << "장착무기: 없음";
	}

	if (pPlayer->bEquip[EQ_ARMOR]) {
		cout << "\t장착방어구: " << pPlayer->tEquip[EQ_ARMOR].strName << endl;
	}
	else {
		cout << "\t장착방어구: 없음" << endl;
	}

	cout << "보유골드: " << pPlayer->tInventory.iGold << " Gold" << endl;
}

void OutputMonster(_tagMonster* pMonster) {
	cout << "===================== Monster =====================" << endl;
	cout << "이름: " << pMonster->strName << "\t레벨: " << pMonster->iLevel << endl;
	cout << "공격력: " << pMonster->iAttackMin << " - " << pMonster->iAttackMax << "\t방어력: " << pMonster->iArmorMin << " - " << pMonster->iArmorMax << endl;
	cout << "체력: " << pMonster->iHP << " / " << pMonster->iHPMax << "\t마나: " << pMonster->iMP << " / " << pMonster->iMPMax << endl;
	cout << "획득 경험치: " << pMonster->iExp << "\t획득 골드: " << pMonster->iGoldMin << " - " << pMonster->iGoldMax << endl << endl;
}

int OutputBattleMenu() {
	cout << "1. 공격" << endl;
	cout << "2. 도망가기" << endl << endl;
	cout << "메뉴를 선택하세요: ";
	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= BATTLE_NONE || iMenu > BATTLE_BACK) {
		return BATTLE_NONE;
	}

	return iMenu;
}

void RunBattle(_tagPlayer* pPlayer, _tagMonster* pMonsterArr, int iMenu) {
	_tagMonster tMonster = pMonsterArr[iMenu - 1];

	while (true) {
		system("cls");
		OutputBattleTag(iMenu);

		// 플레이어 출력
		OutputPlayer(pPlayer);

		// 몬스터 출력
		OutputMonster(&tMonster);

		switch (OutputBattleMenu()) {
		case BATTLE_ATTACK:
			break;
		case BATTLE_BACK:
			return;
		}
	}
}

int OutputMapMenu() {
	system("cls");
	cout << "===================== 맵 =====================" << endl;
	cout << "1. 쉬움" << endl;
	cout << "2. 보통" << endl;
	cout << "3. 어려움" << endl;
	cout << "4. 뒤로가기" << endl;
	cout << "맵을 선택하세요: ";

	int iMenu = InputInt();

	if (iMenu == INT_MAX || iMenu <= MT_NONE || iMenu > MT_BACK) {
		return MT_NONE;
	}

	return iMenu;
}

// Map에 관련된 동작 처리
void RunMap(_tagPlayer* pPlayer, _tagMonster* pMonsterArr) {

	bool bLoop = true;

	while (bLoop) {
		int iMenu = OutputMapMenu();

		if (iMenu == MT_BACK) {
			return;
		}

		// 전투를 시작한다.
		RunBattle(pPlayer, pMonsterArr, iMenu);

	}
}

void SetPlayer(_tagPlayer* pPlayer) {

	// 플레이어의 이름을 입력받는다.
	cout << "이름: ";
	cin.getline(pPlayer->strName, NAME_SIZE - 1);

	// 초기 플레이어 정보
	pPlayer->eJob = (JOB)SelectJob();
	pPlayer->iLevel = 1;
	pPlayer->iExp = 0;
	pPlayer->tInventory.iGold = 10000;

	switch (pPlayer->eJob) {
	case JOB_KNIGHT:
		strcpy_s(pPlayer->strJobName, "기사");
		pPlayer->iAttackMin = 5;
		pPlayer->iAttackMax = 10;
		pPlayer->iArmorMin = 15;
		pPlayer->iArmorMax = 20;
		pPlayer->iHP = 500;
		pPlayer->iHPMax = 500;
		pPlayer->iMP = 100;
		pPlayer->iMPMax = 100;
		break;
	case JOB_ARCHER:
		strcpy_s(pPlayer->strJobName, "궁수");
		pPlayer->iAttackMin = 10;
		pPlayer->iAttackMax = 15;
		pPlayer->iArmorMin = 10;
		pPlayer->iArmorMax = 15;
		pPlayer->iHP = 400;
		pPlayer->iHPMax = 400;
		pPlayer->iMP = 200;
		pPlayer->iMPMax = 200;
		break;
	case JOB_WIZARD:
		strcpy_s(pPlayer->strJobName, "마법사");
		pPlayer->iAttackMin = 15;
		pPlayer->iAttackMax = 20;
		pPlayer->iArmorMin = 5;
		pPlayer->iArmorMax = 10;
		pPlayer->iHP = 300;
		pPlayer->iHPMax = 300;
		pPlayer->iMP = 300;
		pPlayer->iMPMax = 300;
		break;
	}
}

int SelectJob() {
	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. 기사" << endl;
		cout << "2. 궁수" << endl;
		cout << "3. 마법사" << endl;
		cout << "직업을 선택하세요: ";
		iJob = InputInt();

		if (iJob != JOB_KNIGHT && iJob != JOB_ARCHER && iJob != JOB_WIZARD) {
			iJob = JOB_NONE;
		}
	}

	return iJob;
}

_tagMonster CreateMonster(const char* pName, int iAttackMin, int iAttackMax, int iArmorMin, int iArmorMax, int iHP, int iMP, int iLevel, int iExp, int iGoldMin, int iGoldMax) {
	_tagMonster tMonster = {};

	strcpy_s(tMonster.strName, pName);
	tMonster.iAttackMin = iAttackMin;
	tMonster.iAttackMax = iAttackMax;
	tMonster.iArmorMin = iArmorMin;
	tMonster.iArmorMax = iArmorMax;
	tMonster.iHP = iHP;
	tMonster.iHPMax = iHP;
	tMonster.iMP = iMP;
	tMonster.iMPMax = iMP;
	tMonster.iLevel = iLevel;
	tMonster.iExp = iExp;
	tMonster.iGoldMin = iGoldMin;
	tMonster.iGoldMax = iGoldMax;

	return tMonster;
}

void SetMonster(_tagMonster* pMonsterArr) {
	pMonsterArr[0] = CreateMonster("고블린", 20, 30, 2, 5, 100, 10, 1, 1000, 500, 1500);
	pMonsterArr[1] = CreateMonster("트롤", 80, 130, 60, 90, 2000, 100, 5, 7000, 6000, 8000);
	pMonsterArr[2] = CreateMonster("드래곤", 250, 500, 200, 400, 30000, 20000, 10, 30000, 20000, 50000);
}