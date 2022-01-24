#ifndef structures
#define structures
#include <string>
#include "globals.h"
using namespace std;

/* ������ */
struct Effect{
	bool is;
	unsigned int dmg;
	unsigned int turns;
};

/* ������ �������� */
struct Status{
	Effect bleeding;
	Effect poison;
	bool stun;
};

/* ����������� */
struct Abilities{
	string name;
	string description[8];
	float modDmg;
	float modAcc;
	float modCrit;
	float stun;
	float bleedChance;
	unsigned int bleedDmg;
	unsigned int bleedTurns;
	float poisonChance;
	unsigned int poisonDmg;
	unsigned int poisonTurns;
};

/* �������������� �����*/
struct Stats{
	string name;
	string type;
	unsigned int maxhp;
	int hp;
	unsigned int minDmg;
	unsigned int maxDmg;
	float acc;
	float crit;
	float dodge;
	float def;
	unsigned int gold;
	unsigned int keys;
	Abilities ability[4];
};

/* �������������� ������*/
struct EnemyStats{
	string name;
	string type;
	int hp;
	unsigned int minDmg;
	unsigned int maxDmg;
	float acc;
	float crit;
	float dodge;
	float def;
	Status status;
	float bleedingResist;
	float poisonResist;
	float stunResist;
};

extern Stats *Heroes;
extern Stats hero;
extern EnemyStats Enemies[20];
	
/* ��������� ������� */
struct MAP{
	bool room;
	unsigned int type;
	unsigned int nearRooms;
	bool explored;
};
extern MAP Map[13][9];

/* ��������� ��������� */
struct Item{
	string name;
	string description;
	unsigned int price;
	void (*Buf)();
	void (*Debuf)();
};
extern Item Goods[5];
extern Item Items[42];
#endif
