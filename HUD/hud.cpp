#include "hud.h"
#include "parameters.h"
#include "structures.h"
#include "globals.h"
#include <iostream>
#include <cstring>

/* Функции для вывода характеристик */
void PrintHeroName(){
	cursor(3, 3);
	color(8);
	cout << "Name: ";
	color(7);
	cout << hero.name;
}
void PrintHeroClass(){
	cursor(3, 4);
	color(8);
	cout << "Class: ";
	color(7);
	cout << hero.type;
}
void PrintHeroHP(){
	cursor(3, 5);
	color(8);
	cout << "HP: ";
	if(hero.hp < hero.maxhp){
		color(12); cout << hero.hp;
		color(7); cout << "/";
		color(8); cout << hero.maxhp;
	}
	else{
		color(7); cout << hero.hp;
		color(8); cout << "/";
		color(7); cout << hero.maxhp;		
	}
	cout << "  ";
}
void PrintHeroDmg(){
	cursor(3, 6);
	color(8);
	cout << "Damage: ";
	color(7);
	cout << hero.minDmg <<'-'<< hero.maxDmg;
	cout << "  ";
}
void PrintHeroAccuracy(){
	cursor(3, 7);
	color(8);
	cout << "Accuracy: ";
	color(7);
	cout << hero.acc*100 <<'%';
	cout << "  ";
}
void PrintHeroCrit(){
	cursor(3, 8);
	color(8);
	cout << "Crit chance: ";
	color(7);
	cout << hero.crit*100 <<'%';
	cout << "  ";
}
void PrintHeroDodge(){
	cursor(3, 9);
	color(8);
	cout << "Dodge: ";
	color(7);
	cout << hero.dodge*100 <<'%';
	cout << "  ";
}
void PrintHeroDefence(){
	cursor(3, 10);
	color(8);
	cout << "Defence: ";
	color(7);
	cout << hero.def*100 <<'%';
	cout << "  ";
}
void PrintHeroGold(){
	cursor(3, 12);
	color(8);
	cout << "Gold: ";
	color(14);
	cout << hero.gold;
	cout << "  ";
}
void PrintHeroKeys(){
	cursor(3, 13);
	color(8);
	cout << "Keys: ";
	color(14);
	cout << hero.keys;
	cout << "  ";
}

/* Функции для вывода характеристик врага*/
void PrintEnemyName(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 3);
	color(8);
	cout << "Name: ";
	color(7);
	cout << enemy.name;
}
void PrintEnemyClass(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 4);
	color(8);
	cout << "Class: ";
	color(7);
	cout << enemy.type;
}
void PrintEnemyHP(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 5);
	color(8);
	cout << "HP: ";
	color(12);
	cout << enemy.hp << "     ";
}
void PrintEnemyDmg(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 6);
	color(8);
	cout << "Damage: ";
	color(7);
	cout << enemy.minDmg <<'-'<< enemy.maxDmg;
}
void PrintEnemyAccuracy(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 7);
	color(8);
	cout << "Accuracy: ";
	color(7);
	cout << enemy.acc*100 <<'%';
}
void PrintEnemyCrit(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 8);
	color(8);
	cout << "Crit chance: ";
	color(7);
	cout << enemy.crit*100 <<'%';
}
void PrintEnemyDodge(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 9);
	color(8);
	cout << "Dodge: ";
	color(7);
	cout << enemy.dodge*100 <<'%';
}
void PrintEnemyDefence(EnemyStats enemy){
	cursor(WIDTH-ENEMY_W-1, 10);
	color(8);
	cout << "Defence: ";
	color(7);
	cout << enemy.def*100 <<'%';
}
void PrintEnemyStatus(EnemyStats enemy){
	unsigned int x, y, i, j;
	cursor(x = WIDTH-ENEMY_W-1, y = 11);
	for(j=1; j<=3; j++){
		for(i=1; i<ENEMY_W; i++) cout <<' ';
		cursor(x, ++y);
	}	
	color(7);
	cursor(x, y = 11);
	if(enemy.status.stun){
		color(14);
		cout << "Stunned!";
		cursor(x, ++y);
	}
	if(enemy.status.bleeding.is){
		color(12);
		cout << "Bleeding: " << enemy.status.bleeding.dmg <<" / "<< enemy.status.bleeding.turns;
		cursor(x, ++y);
	}
	if(enemy.status.poison.is){
		color(10);
		cout << "Poisoned: " << enemy.status.poison.dmg <<" / "<< enemy.status.poison.turns;
		cursor(x, ++y);
	}
	if((!enemy.status.stun) && (!enemy.status.bleeding.is) && (!enemy.status.poison.is)){
		cursor(x, y = 12);
		cout << "<< No effects >>";
	}
}

/* Вывести все характеристи героя*/
void PrintAllStats(){
	PrintHeroName();
	PrintHeroClass();
	PrintHeroHP();
	PrintHeroDmg();
	PrintHeroAccuracy();
	PrintHeroCrit();
	PrintHeroDodge();
	PrintHeroDefence();
	PrintHeroGold();
	PrintHeroKeys();
}

/* Вывести все характеристи врага*/
void PrintAllEnemyStats(EnemyStats enemy){
	PrintEnemyName(enemy);
	PrintEnemyClass(enemy);
	PrintEnemyHP(enemy);
	PrintEnemyDmg(enemy);
	PrintEnemyAccuracy(enemy);
	PrintEnemyCrit(enemy);
	PrintEnemyDodge(enemy);
	PrintEnemyDefence(enemy);
	PrintEnemyStatus(enemy);
}

/* Нарисовать рамку */
void DrawHudBox(int HUDx, int HUDy, int width, int height, string head){
	int x, y, i, j;	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	string buffer;
	
	/* Верхняя граница окна */
	cursor(x = HUDx, y = HUDy);
	buffer += (char)201;
	for(j=1; j <= width; j++) buffer += (char)205;
	buffer += (char)187;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	
	/* Область окна */
	cursor(x, ++y);
	for(i=1; i<=height; i++){
		buffer += (char)186;
		for(j=1; j<=width; j++)	buffer += ' ';
		buffer += (char)186;
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		cursor(x, ++y);
	}
	
	/* Нижняя граница */
	buffer += (char)200;
	for(j=1; j <= width; j++) buffer += (char)205;
	buffer += (char)188;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	
	/* Черта под заголовком */
	cursor(x = HUDx, y = HUDy+2);
	buffer += (char)204;
	for(j=1; j <= width; j++) buffer += (char)205;
	buffer += (char)185;
	fputs(buffer.c_str(), stdout);
	buffer.clear();	
	
	/* Заголовок */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	cursor(x = HUDx+(width-head.length())/2+1, y = HUDy+1);
	cout << head;	
}
