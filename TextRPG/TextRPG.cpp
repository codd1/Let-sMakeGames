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
	JOB_WIZARD
};

enum BATTLE {
	BATTLE_NONE,
	BATTLE_ATTACK,
	BATTLE_BACK
};

#define NAME_SIZE	32

struct _tagInventory {
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

int main() {

	srand((unsigned int)time(0));

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

	tPlayer.eJob = (JOB)iJob;
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

	// ������ ����
	strcpy_s(tMonsterArr[0].strName, "������");
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
					cout << "����: " << tPlayer.iLevel << "\t����ġ: " << tPlayer.iExp << endl;
					cout << "���ݷ�: " << tPlayer.iAttackMin << " - " << tPlayer.iAttackMax << "\t����: " << tPlayer.iArmorMin << " - " << tPlayer.iArmorMax << endl;
					cout << "ü��: " << tPlayer.iHP << " / " << tPlayer.iHPMax << "\t����: " << tPlayer.iMP << " / " << tPlayer.iMPMax << endl;
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
						int iAttack = rand() % (tPlayer.iAttackMax - tPlayer.iAttackMin + 1) + tPlayer.iAttackMin;
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

							system("pause");
							break;
						}

						// ���Ͱ� ����ִٸ� �÷��̾ �����Ѵ�.
						iAttack = rand() % (tMonster.iAttackMax - tMonster.iAttackMin + 1) + tMonster.iAttackMin;
						iArmor = rand() % (tPlayer.iArmorMax - tPlayer.iArmorMin + 1) + tPlayer.iArmorMin;

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
			break;
		case MM_INVENTORY:
			break;
		default:
			cout << "�߸� �����߽��ϴ�." << endl;
			break;
		}


	}


	return 0;
}