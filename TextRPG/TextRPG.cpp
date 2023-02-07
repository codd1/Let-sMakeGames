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
	char strDesc[ITEM_DESC_LENGTH];		// ������ ����
};

struct _tagInventory {
	_tagItem tItem[INVENTORY_MAX];		// �κ��丮 ĭ��
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
	int iExp;		// ���� óġ �� �÷��̾� ȹ�� ����ġ
	int iGoldMin;	// ���� óġ �� �÷��̾� ȹ�� ���
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

	// �������� �ʿ��� ����ġ ����� �����.
	const int iLevelUpExp[LEVEL_MAX] = { 4000,10000,20000,35000,50000,70000,100000,150000,200000,400000 };

	// JOB_END == 4.
	// ������ 3���̹Ƿ� -1 ���־ �迭�� �� �������� �����ϵ��� �Ѵ�.
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

	// ������ ������ �� �÷��̾� ������ �����Ѵ�.
	_tagPlayer tPlayer = {};

	cout << "�̸�: ";
	cin.getline(tPlayer.strName, NAME_SIZE - 1);

	int iJob = JOB_NONE;
	while (iJob == JOB_NONE) {
		system("cls");
		cout << "1. ���" << endl;
		cout << "2. �ü�" << endl;
		cout << "3. ������" << endl;
		cout << "������ �����ϼ���: ";
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

	// �ʱ� �÷��̾� ����
	tPlayer.iLevel = 1;
	tPlayer.iExp = 0;
	tPlayer.eJob = (JOB)iJob;
	tPlayer.tInventory.iGold = 10000;

	switch (tPlayer.eJob) {
	case JOB_KNIGHT:
		strcpy_s(tPlayer.strJobName, "���");
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
		strcpy_s(tPlayer.strJobName, "�ü�");
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
		strcpy_s(tPlayer.strJobName, "������");
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

	// ���͸� �����Ѵ�.
	_tagMonster tMonsterArr[MT_BACK - 1] = {};

	// ��� ����
	strcpy_s(tMonsterArr[0].strName, "���");
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

	// Ʈ�� ����
	strcpy_s(tMonsterArr[1].strName, "Ʈ��");
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

	// �巡�� ����
	strcpy_s(tMonsterArr[2].strName, "�巡��");
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


	// �������� �Ǹ��� ������ ����� �����Ѵ�.
	_tagItem tStoreWeapon[STORE_WEAPON_MAX] = {};
	_tagItem tStoreArmor[STORE_ARMOR_MAX] = {};

	// ���� - �콼 ���� ����
	strcpy_s(tStoreWeapon[0].strName, "�콼 ����");
	strcpy_s(tStoreWeapon[0].strTypeName, "����");
	tStoreWeapon[0].iMin = 30;
	tStoreWeapon[0].iMax = 50;
	tStoreWeapon[0].iPrice = 5000;
	tStoreWeapon[0].iSell = tStoreWeapon[0].iPrice * 0.7f;
	tStoreWeapon[0].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[0].strDesc, "���� �μ����� �𸣴� �콼 �����̴�.");

	// ���� - �Ϲ� ���� ����
	strcpy_s(tStoreWeapon[1].strName, "�Ϲ� ����");
	strcpy_s(tStoreWeapon[1].strTypeName, "����");
	tStoreWeapon[1].iMin = 400;
	tStoreWeapon[1].iMax = 500;
	tStoreWeapon[1].iPrice = 12000;
	tStoreWeapon[1].iSell = tStoreWeapon[1].iPrice * 0.7f;
	tStoreWeapon[1].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[1].strDesc, "����� ���������� �� �����غ��δ�.");

	// ���� - ����� ���� ����
	strcpy_s(tStoreWeapon[2].strName, "����� ����");
	strcpy_s(tStoreWeapon[2].strTypeName, "����");
	tStoreWeapon[2].iMin = 1200;
	tStoreWeapon[2].iMax = 1500;
	tStoreWeapon[2].iPrice = 20000;
	tStoreWeapon[2].iSell = tStoreWeapon[2].iPrice * 0.7f;
	tStoreWeapon[2].eType = IT_WEAPON;
	strcpy_s(tStoreWeapon[2].strDesc, "�� ���迡�� ���� ������ ����� �����̴�. �ҹ��� ���ϸ� ����Į������� �Ҹ���.");


	// �� - ���� �� ����
	strcpy_s(tStoreArmor[0].strName, "���� ��");
	strcpy_s(tStoreArmor[0].strTypeName, "��");
	tStoreArmor[0].iMin = 30;
	tStoreArmor[0].iMax = 50;
	tStoreArmor[0].iPrice = 5000;
	tStoreArmor[0].iSell = tStoreArmor[0].iPrice * 0.7f;
	tStoreArmor[0].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[0].strDesc, "���� ���� ���� ���̴�.");

	// �� - ������ �� ����
	strcpy_s(tStoreArmor[1].strName, "������ ��");
	strcpy_s(tStoreArmor[1].strTypeName, "��");
	tStoreArmor[1].iMin = 200;
	tStoreArmor[1].iMax = 300;
	tStoreArmor[1].iPrice = 12000;
	tStoreArmor[1].iSell = tStoreArmor[1].iPrice * 0.7f;
	tStoreArmor[1].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[1].strDesc, "����غ��̴� ������ ������ ���̴�.");

	// �� - ����� �� ����
	strcpy_s(tStoreArmor[2].strName, "����� ��");
	strcpy_s(tStoreArmor[2].strTypeName, "��");
	tStoreArmor[2].iMin = 800;
	tStoreArmor[2].iMax = 1000;
	tStoreArmor[2].iPrice = 20000;
	tStoreArmor[2].iSell = tStoreArmor[2].iPrice * 0.7f;
	tStoreArmor[2].eType = IT_ARMOR;
	strcpy_s(tStoreArmor[2].strDesc, "�� ���迡�� ���� ������ ����� ���̴�. ������ ���ϸ� �������� �� ���� ���� �ڴ� �ƹ��� ���ٰ� �Ѵ�.");


	while (true) {
		system("cls");
		cout << "===================== �κ� =====================" << endl;
		cout << "1. ��" << endl;
		cout << "2. ����" << endl;
		cout << "3. �κ��丮" << endl;
		cout << "4. ����" << endl;
		cout << "�޴��� �����ϼ���: ";

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
				cout << "===================== �� =====================" << endl;
				cout << "1. ����" << endl;
				cout << "2. ����" << endl;
				cout << "3. �����" << endl;
				cout << "4. �ڷΰ���" << endl;
				cout << "���� �����ϼ���: ";
				cin >> iMenu;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1024, '\n');
					continue;
				}

				if (iMenu == MT_BACK) {
					break;
				}

				// ������ �޴� -1�� ���� �迭�� �ε����� �ȴ�.
				_tagMonster tMonster = tMonsterArr[iMenu - 1];

				while (true) {
					system("cls");

					switch (iMenu) {
					case MT_EASY:
						cout << "===================== ���� =====================" << endl;
						break;
					case MT_NORMAL:
						cout << "===================== ���� =====================" << endl;
						break;
					case MT_HARD:
						cout << "===================== ����� =====================" << endl;
						break;
					}

					// �÷��̾� ������ ����Ѵ�.
					cout << "===================== Player =====================" << endl;
					cout << "�̸�: " << tPlayer.strName << "\t����: " << tPlayer.strJobName << endl;
					cout << "����: " << tPlayer.iLevel << "\t����ġ: " << tPlayer.iExp << " / " << iLevelUpExp[tPlayer.iLevel - 1] << endl;

					// ���⸦ �����ϰ� ���� ��� ���ݷ¿� ������ݷ��� �߰��Ͽ� ����Ѵ�.
					if (tPlayer.bEquip[EQ_WEAPON] == true) {
						cout << "���ݷ�: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_WEAPON].iMin << " - " << tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_WEAPON].iMax;
					}
					else {
						cout << "���ݷ�: " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax;
					}

					// ���� �����ϰ� ���� ��� ���¿� �� ������ �߰��Ͽ� ����Ѵ�.
					if (tPlayer.bEquip[EQ_ARMOR] == true) {
						cout << "\t����: " << tPlayer.iAttackMin << " + " << tPlayer.tEquip[EQ_ARMOR].iMin << " - " << tPlayer.iAttackMax << " + " << tPlayer.tEquip[EQ_ARMOR].iMax << endl;
					}
					else {
						cout << "\t����: " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;
					}

					cout << "ü��: " << tPlayer.iHP << " / " << tPlayer.iHPMax << "\t����: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;

					if (tPlayer.bEquip[EQ_WEAPON]) {
						cout << "��������: " << tPlayer.tEquip[EQ_WEAPON].strName;
					}
					else {
						cout << "��������: ����";
					}

					if (tPlayer.bEquip[EQ_ARMOR]) {
						cout << "\t������: " << tPlayer.tEquip[EQ_ARMOR].strName << endl;
					}
					else {
						cout << "\t������: ����" << endl;
					}

					cout << "�������: " << tPlayer.tInventory.iGold << " Gold" << endl;

					// ���� ���� ���
					cout << "===================== Monster =====================" << endl;
					cout << "�̸�: " << tMonster.strName << "\t����: " << tMonster.iLevel << endl;
					cout << "���ݷ�: " << tMonster.iAttackMin << " - " << tMonster.iAttackMax << "\t����: " << tMonster.iArmorMin << " - " << tMonster.iArmorMax << endl;
					cout << "ü��: " << tMonster.iHP << " / " << tMonster.iHPMax << "\t����: " << tMonster.iMP << " / " << tMonster.iMPMax << endl;
					cout << "ȹ�� ����ġ: " << tMonster.iExp << "\tȹ�� ���: " << tMonster.iGoldMin << " - " << tMonster.iGoldMax << endl << endl;

					cout << "1. ����" << endl;
					cout << "2. ��������" << endl << endl;
					cout << "�޴��� �����ϼ���: ";
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
						// ���� ��� Min 5 Max 15 ��� ������ ���
						// 15-5+1�� �ϸ� 11�� �ȴ�. 11�� ���� �������� 0~10�� ������ �ǰ�
						// ���⿡ Min���� 5�� ���ϰ� �Ǹ� 5~15 ���̷� ���� ������ �ȴ�.

						int iAttackMin = tPlayer.iAttackMin;
						int iAttackMax = tPlayer.iAttackMax;

						// ���⸦ �����ϰ� ���� ��� ����� Min, Max�� �����ش�.
						if (tPlayer.bEquip[EQ_WEAPON]) {
							iAttackMin += tPlayer.tEquip[EQ_WEAPON].iMin;
							iAttackMax += tPlayer.tEquip[EQ_WEAPON].iMax;
						}

						int iAttack = rand() % (iAttackMax - iAttackMin + 1) + iAttackMin;
						int iArmor = rand() % (tMonster.iArmorMax - tMonster.iArmorMin + 1) + tMonster.iArmorMin;

						int iDamage = iAttack - iArmor;
						// ���׿������� ���� -> ���ǽ� ? ture�� �� �� : false�� �� �� : 
						iDamage = iDamage < 1 ? 1 : iDamage;	// �ּ� ���������� 1�� �Ѵ�.

						// ���� HP�� ���ҽ�Ų��.
						tMonster.iHP -= iDamage;

						cout << tPlayer.strName << "�� " << tMonster.strName << "���� " << iDamage << " ���ظ� �������ϴ�." << endl;

						// ���Ͱ� �׾��� ��츦 ó���Ѵ�.
						if (tMonster.iHP <= 0) {
							cout << tMonster.strName << " ���Ͱ� ����߽��ϴ�." << endl;

							tPlayer.iExp += tMonster.iExp;
							int iGold = (rand() % (tMonster.iGoldMax - tMonster.iGoldMin + 1) + tMonster.iGoldMin);
							tPlayer.tInventory.iGold += iGold;

							cout << tMonster.iExp << " ����ġ�� ȹ���߽��ϴ�." << endl;
							cout << iGold << " Gold�� ȹ���߽��ϴ�." << endl;

							tMonster.iHP = tMonster.iHPMax;
							tMonster.iMP = tMonster.iMPMax;

							// �������� �ߴ��� üũ�Ѵ�.
							if (tPlayer.iExp >= iLevelUpExp[tPlayer.iLevel - 1]) {
								// �÷��̾� ����ġ�� �������� �ʿ��� ����ġ��ŭ �����Ѵ�.
								tPlayer.iExp -= iLevelUpExp[tPlayer.iLevel - 1];

								// ������ ������Ų��.
								tPlayer.iLevel++;

								cout << "������ �߽��ϴ�!" << endl;

								// �ɷ�ġ�� ��½�Ų��.
								int iJobIndex = tPlayer.eJob - 1;	// ���� �ε���
								int iHPUp = rand() % (tLvUpTable[iJobIndex].iHPMax - tLvUpTable[iJobIndex].iHPMin + 1) + tLvUpTable[iJobIndex].iHPMin;
								int iMPUp = rand() % (tLvUpTable[iJobIndex].iMPMax - tLvUpTable[iJobIndex].iMPMin + 1) + tLvUpTable[iJobIndex].iMPMin;

								tPlayer.iAttackMin += tLvUpTable[iJobIndex].iAttackMin;
								tPlayer.iAttackMax += tLvUpTable[iJobIndex].iAttackMax;
								tPlayer.iArmorMin += tLvUpTable[iJobIndex].iArmorMin;
								tPlayer.iArmorMax += tLvUpTable[iJobIndex].iArmorMax;

								tPlayer.iHPMax += iHPUp;
								tPlayer.iMPMax += iMPUp;

								// ü�°� ������ ȸ����Ų��.
								tPlayer.iHP = tPlayer.iHPMax;
								tPlayer.iMP = tPlayer.iMPMax;

							}

							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) + tMonster.iAttackMin;

						int iArmorMin = tPlayer.iArmorMin;
						int iArmorMax = tPlayer.iArmorMax;

						if (tPlayer.bEquip[EQ_ARMOR]) {
							iArmorMin += tPlayer.tEquip[EQ_ARMOR].iMin;
							iArmorMax += tPlayer.tEquip[EQ_ARMOR].iMax;
						}

						iArmor = rand() % (iArmorMax - iArmorMin + 1) + iArmorMin;

						iDamage = iAttack - iArmor;
						iDamage = iDamage < 1 ? 1 : iDamage;	// �ּ� ���������� 1�� �Ѵ�.

						// �÷��̾��� HP�� ���ҽ�Ų��.
						tPlayer.iHP -= iDamage;

						cout << tMonster.strName << "�� " << tPlayer.strName << "���� " << iDamage << " ���ظ� �������ϴ�." << endl;

						// �÷��̾ �׾��� ���
						if (tPlayer.iHP <= 0) {
							cout << tPlayer.strName << " �÷��̾ ����߽��ϴ�." << endl;

							int iExp = tPlayer.iExp * 0.1f;
							int iGold = tPlayer.tInventory.iGold * 0.1f;

							tPlayer.iExp -= iExp;
							tPlayer.tInventory.iGold -= iGold;

							cout << iExp << " ����ġ�� �Ҿ����ϴ�." << endl;
							cout << iGold << " Gold�� �Ҿ����ϴ�." << endl;

							// �÷��̾��� HP�� MP�� ȸ���Ѵ�.
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
				cout << "===================== ���� =====================" << endl;
				cout << "1. �������" << endl;
				cout << "2. ������" << endl;
				cout << "3. �ڷΰ���" << endl;
				cout << "������ �����ϼ���: ";
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
						cout << "===================== ������� =====================" << endl;
						// �Ǹ� ����� �����ش�.
						for (int i = 0; i < STORE_WEAPON_MAX; i++) {
							cout << "===================== " << i + 1 << ". " << tStoreWeapon[i].strName << " =====================" << endl;
							cout << "������ Ÿ�� : " << tStoreWeapon[i].strTypeName << endl;
							cout << "�ɷ�ġ: " << tStoreWeapon[i].iMin << " - " << tStoreWeapon[i].iMax << endl;
							cout << "���Ű���: " << tStoreWeapon[i].iPrice << " Gold\t�ǸŰ���: " << tStoreWeapon[i].iSell << " Gold" << endl;
							cout << "������ ����: " << tStoreWeapon[i].strDesc << endl << endl;
						}
						cout << "===================== 4. �ڷΰ��� =====================" << endl << endl;
						cout << "���� ���� Gold: " << tPlayer.tInventory.iGold << " Gold" << endl;
						cout << "�޴��� �����ϼ���: ";
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreWeapon[0].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[0].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreWeapon[1].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[1].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreWeapon[2].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreWeapon[2].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
						cout << "===================== �� ���� =====================" << endl;
						// �Ǹ� ����� �����ش�.
						for (int i = 0; i < STORE_ARMOR_MAX; i++) {
							cout << "===================== " << i + 1 << ". " << tStoreArmor[i].strName << " =====================" << endl;
							cout << "������ Ÿ�� : " << tStoreArmor[i].strTypeName << endl;
							cout << "�ɷ�ġ: " << tStoreArmor[i].iMin << " - " << tStoreArmor[i].iMax << endl;
							cout << "���Ű���: " << tStoreArmor[i].iPrice << " Gold\t�ǸŰ���: " << tStoreArmor[i].iSell << " Gold" << endl;
							cout << "������ ����: " << tStoreArmor[i].strDesc << endl << endl;
						}
						cout << "===================== 4. �ڷΰ��� =====================" << endl << endl;
						cout << "�޴��� �����ϼ���: ";
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreArmor[0].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[0].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreArmor[1].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[1].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
								cout << "���� �Ұ�: �ܾ��� �����մϴ�." << endl;
							}
							else if (tPlayer.tInventory.iItemCount == INVENTORY_MAX) {
								cout << "���� �Ұ�: �κ��丮 ������ �����մϴ�." << endl;
							}
							else {
								cout << "���� ����: " << tStoreArmor[2].strName << " �������� �����߽��ϴ�." << endl;

								tPlayer.tInventory.iGold -= tStoreArmor[2].iPrice;
								cout << "�ܾ�: " << tPlayer.tInventory.iGold << " Gold" << endl;

								// �κ��丮�� ������ �߰�
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
				cout << "===================== �κ��丮 =====================" << endl;
				for (int i = 0; i < tPlayer.tInventory.iItemCount; i++) {
					cout << i + 1 << ". �̸�: " << tPlayer.tInventory.tItem[i].strName << endl;
					cout << "������ Ÿ�� : " << tPlayer.tInventory.tItem[i].strTypeName << endl;
					cout << "�ɷ�ġ: " << tPlayer.tInventory.tItem[i].iMin << " - " << tPlayer.tInventory.tItem[i].iMax << endl;
					cout << "���Ű���: " << tPlayer.tInventory.tItem[i].iPrice << " Gold\t�ǸŰ���: " << tPlayer.tInventory.tItem[i].iSell << " Gold" << endl;
					cout << "������ ����: " << tPlayer.tInventory.tItem[i].strDesc << endl << endl;
				}
				cout << endl << "�� ������ ����: " << tPlayer.tInventory.iItemCount << endl << endl;

				cout << tPlayer.tInventory.iItemCount + 1 << ". �ڷΰ���" << endl;
				cout << "������ �������� �����ϼ���: ";

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
					cout << "�߸� �����߽��ϴ�." << endl;
					system("pause");
					continue;
				}

				// ������ �ε����� �����ش�.
				int idx = iMenu - 1;

				// ����� �������� ��� �ش� �������� ������ ���� ���� ������ �����Ѵ�.
				EQUIP eq;

				switch (tPlayer.tInventory.tItem[idx].eType) {
				case IT_WEAPON:
					eq = EQ_WEAPON;
					break;
				case IT_ARMOR:
					eq = EQ_ARMOR;
					break;
				}

				// �������� �����Ǿ� ���� ��� ���� �Ǿ��ִ� �����۰� ������ �������� ��ü���ش�. (Swap)
				if (tPlayer.bEquip[eq] == true) {
					_tagItem tSwap = tPlayer.tEquip[eq];
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];
					tPlayer.tInventory.tItem[idx] = tSwap;
				}

				// �����Ǿ����� ���� ��� �κ��丮 �������� ����â���� �ű�� �κ��丮�� 1ĭ ������Եȴ�.
				else {
					tPlayer.tEquip[eq] = tPlayer.tInventory.tItem[idx];

					for (int i = idx; i < tPlayer.tInventory.iItemCount - 1; i++) {
						tPlayer.tInventory.tItem[i] = tPlayer.tInventory.tItem[i + 1];
					}

					tPlayer.tInventory.iItemCount--;

					// ���������Ƿ� true�� ����
					tPlayer.bEquip[eq] = true;
				}

				cout << tPlayer.tEquip[eq].strName << " �������� �����߽��ϴ�." << endl;
				system("pause");
			}
			break;
		default:
			cout << "�߸� �����߽��ϴ�." << endl;
			break;
		}


	}


	return 0;
}