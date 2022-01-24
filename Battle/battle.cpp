#include "battle.h"
#include "mainmenu.h"
#include "structures.h"
#include "abilitiesnav.h"
#include "hud.h"
#include "globals.h"
#include "parameters.h"
#include <windows.h>
#include <MMSystem.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>

/* Звук удара */
void ShotSound(){
	unsigned int P;
	if((P = rand() % 2) == 1) mciSendString("play sounds\\shot.mp3", NULL, 0, NULL);
	else mciSendString("play sounds\\shot2.mp3", NULL, 0, NULL);
}
void BeastShotSound(){
	mciSendString("play sounds\\beast_shot.mp3", NULL, 0, NULL);
}
void SpiritShotSound(){
	mciSendString("play sounds\\spirit_shot.mp3", NULL, 0, NULL);
}

/* Ход героя */
int HeroTurn(EnemyStats &enemy, unsigned int &AbilityCode, string message[4]){
	unsigned int P, Damage, i;
	SelectAbility(AbilityCode);
	if(AbilityNavigation(AbilityCode) == Back) return Back;
	for(i=0; i<4; i++) message[i] = "0";
	i=0;
	
	/* Проверка на попадание */
	if((P = rand() % 101) < (hero.acc*hero.ability[AbilityCode].modAcc*100*(1-enemy.dodge))){
		Damage = round((rand() % (hero.maxDmg-hero.minDmg+1) + hero.minDmg)*(1-enemy.def)*(hero.ability[AbilityCode].modDmg));
		
		/* Проверка на Crit */
		if((P = rand() % 101) < (hero.crit*100*hero.ability[AbilityCode].modCrit)){
			Damage *= 5;
			message[0] = "Critical hit " + to_string(Damage) + "!!!";
		}
		else message[0] = "Damage " + to_string(Damage) + "!";
		enemy.hp -= Damage;
		
		/* Проверка на кровотечение */
		if(hero.ability[AbilityCode].bleedChance){			
			if((P = rand() % 101) < (hero.ability[AbilityCode].bleedChance*100*(1-enemy.bleedingResist))){
				enemy.status.bleeding.is = 1;
				enemy.status.bleeding.dmg += hero.ability[AbilityCode].bleedDmg;
				enemy.status.bleeding.turns += hero.ability[AbilityCode].bleedTurns;
				message[1] = "Bleeding: " + to_string(hero.ability[AbilityCode].bleedDmg) + " Dmg / " + to_string(hero.ability[AbilityCode].bleedTurns) + " turns";
			}
			else message[1] = "Resistance to Bleeding!";
		}
		
		/* Проверка на отравление */
		if(hero.ability[AbilityCode].poisonChance){			
			if((P = rand() % 101) < (hero.ability[AbilityCode].poisonChance*100*(1-enemy.poisonResist))){
				enemy.status.poison.is = 1;
				enemy.status.poison.dmg += hero.ability[AbilityCode].poisonDmg;
				enemy.status.poison.turns += hero.ability[AbilityCode].poisonTurns;
				message[2] = "Poison: " + to_string(hero.ability[AbilityCode].poisonDmg) + " Dmg / " + to_string(hero.ability[AbilityCode].poisonTurns) + " turns";
			}
			else message[2] = "Resistance to Poison!";		
		}
		
		/* Проверка на огрлушение */
		if(hero.ability[AbilityCode].stun){		
			if((P = rand() % 101) < (hero.ability[AbilityCode].stun*100*(1-enemy.stunResist))){
				enemy.status.stun = 1;
				message[3] = enemy.name + " is stunned!";
			}
			else message[3] = "Resistance to stun!";
		}
		ShotSound();				
	}
	else{
		message[0] = "You missed!";
		mciSendString("play sounds\\missing.mp3", NULL, 0, NULL);
	}
	return Next;
}

/* Ход врага */
void EnemyTurn(EnemyStats &enemy){
	unsigned int P, Damage, x, y, j;
	string s;
	
	/* Проверка на кровотечение */
	if(enemy.status.bleeding.is){
		enemy.hp -= enemy.status.bleeding.dmg;
		s = "-" + to_string(enemy.status.bleeding.dmg) + " HP from Bleeding!";
		DrawMenuBox(x = (WIDTH-s.length()-7), y = ENEMY_H+3, s.length()+2, 1);
		cursor(x+2, y+1);
		for(j=0; j < s.length(); j++){
			if(isalpha(s[j])) color(8);
			if(isdigit(s[j])) color(12);
			cout << s[j];
		}
		PrintEnemyHP(enemy);
		mciSendString("play sounds\\bleed.mp3 wait", NULL, 0, NULL);	
		Sleep(2500);
		HideMenuBox(x, y, s.length()+2, 1);		
		if(enemy.hp <= 0) return;
		enemy.status.bleeding.turns --;
		if(!enemy.status.bleeding.turns){
			enemy.status.bleeding.is = 0;
			enemy.status.bleeding.dmg = 0;
		}
		PrintEnemyStatus(enemy);
	}
	
	/* Проверка на отравление */
	if(enemy.status.poison.is){
		enemy.hp -= enemy.status.poison.dmg;
		s = "-" + to_string(enemy.status.poison.dmg) + " HP from Poison!";
		DrawMenuBox(x = (WIDTH-s.length()-7), y = ENEMY_H+3, s.length()+2, 1);;
		cursor(x+2, y+1);
		for(j=0; j < s.length(); j++){
			if(isalpha(s[j])) color(8);
			if(isdigit(s[j])) color(10);
			cout << s[j];
		}
		PrintEnemyHP(enemy);
		mciSendString("play sounds\\bleed.mp3 wait", NULL, 0, NULL);		
		Sleep(2500);
		HideMenuBox(x, y, s.length()+2, 1);		
		if(enemy.hp <= 0) return;
		enemy.status.poison.turns --;
		if(!enemy.status.poison.turns){
			enemy.status.poison.is = 0;
			enemy.status.poison.dmg = 0;
		}
		PrintEnemyStatus(enemy);
	}
	
	/* Проверка на оглушение */
	if(enemy.status.stun){
		enemy.status.stun = 0;
		s = enemy.name + " is not stunned anymore!";
		DrawMenuBox(x = (WIDTH-s.length()-7), y = ENEMY_H+3, s.length()+2, 1);
		cursor(x+2, y+1);
		color(8);
		cout << s;
		PrintEnemyStatus(enemy);
		Sleep(2500);
		HideMenuBox(x, y, s.length()+2, 1);		
		return;
	}
	
	/* Удар врага */
	if((P = rand() % 101) < (enemy.acc*100*(1-hero.dodge))){
		Damage = round((rand() % (enemy.maxDmg-enemy.minDmg+1) + enemy.minDmg)*(1-hero.def));
		if((P = rand() % 101) < (enemy.crit*100)){
			Damage *= 5;
			s = "-" + to_string(Damage) + " HP from Critical Hit!!!";
			ShotSound();
		}
		else s = "-" + to_string(Damage) + " HP!";
		hero.hp -= Damage;
		if(enemy.type == "Spirit") SpiritShotSound();
		else
		if(enemy.type == "Beast") BeastShotSound();
		else
		ShotSound();
	}
	else{
		s = enemy.name + " missed!";
		mciSendString("play sounds\\missing.mp3", NULL, 0, NULL);	
	}
	DrawMenuBox(x = 2, y = HERO_H+3, s.length()+2, 1);
	cursor(x+2, y+1);
	for(j=0; j < s.length(); j++){
		color(8);
		if(isdigit(s[j])) color(15);
		cout << s[j];
	}
	PrintHeroHP();
	Sleep(2500);
	HideMenuBox(x, y, s.length()+2, 1);
}

/* Битва */
int Battle(unsigned int EnemyID){
	EnemyStats enemy = Enemies[EnemyID];
	unsigned int AbilityCode = 0, width = 30, height = 6, x, y, i, j, MaxLength, strings;
	string message[4], s;
	
	mciSendString("pause music\\Lord_of_the_Land.mp3", NULL, 0, NULL);
	mciSendString("play music\\Division.mp3 repeat", NULL, 0, NULL);
	mciSendStringA("setaudio music\\Division.mp3 volume to 550", NULL, 0, NULL);
	mciSendString("play sounds\\sword.mp3 wait", NULL, 0, NULL);

	
	DrawHudBox(WIDTH-ENEMY_W-3, 0, ENEMY_W, ENEMY_H, "ENEMY");
	PrintAllEnemyStats(enemy);
	
	/* Обнулить статус врага */
	enemy.status.bleeding.is = 0;
	enemy.status.bleeding.dmg = 0;
	enemy.status.bleeding.turns = 0;
	enemy.status.poison.is = 0;
	enemy.status.poison.dmg = 0;
	enemy.status.poison.turns = 0;
	enemy.status.stun = 0;
	
	Sleep(500);
	while(hero.hp > 0){				
		mciSendString("play sounds\\ring.mp3", NULL, 0, NULL);
		s = "Your Turn";
		DrawMenuBox(x = 2, y = HERO_H+3, s.length()+6, 3);
		cursor(x+4, y+2);
		color(10);
		cout << s;		
		Sleep(3000);
		HideMenuBox(x, y, s.length()+6, 3);
		if(HeroTurn(enemy, AbilityCode, message) == Back){
			mciSendString("stop music\\Division.mp3", NULL, 0, NULL);
			return Back;
		}
		HideDescriptionBox(AbilityCode);
		DrawAbilityBox(AbilityCode, hero.ability[AbilityCode].name, 8);
		
		/* Вычисление высоты и ширины окна сообщения */
		strings = 0;
		MaxLength = 0;
		for(i=0; i<4; i++){
			if(message[i] != "0") strings++;
			if(message[i].length() > MaxLength) MaxLength = message[i].length();
		}
		width = MaxLength+2;
		height = strings;
		
		/* Вывод сообщения об атаке */
		DrawMenuBox(x = (WIDTH-width-6), y = ENEMY_H+3, width, height);
		cursor(x+=2, ++y);
		for(i=0; i<4; i++){
			if(message[i] != "0"){
				switch(i){				
					case 0:
						for(j=0; j < message[i].length(); j++){
							color(8);
							if(isdigit(message[i][j])) color(15);
							cout << message[i][j];
						}
						break;
					case 1:
						for(j=0; j < message[i].length(); j++){
							if(isalpha(message[i][j])) color(8);
							if(isdigit(message[i][j])) color(12);
							cout << message[i][j];
						}
						break;
					case 2:
						for(j=0; j < message[i].length(); j++){
							if(isalpha(message[i][j])) color(8);
							if(isdigit(message[i][j])) color(10);
							cout << message[i][j];
						}
						break;
					case 3:
						color(8);
						cout << message[i];
						break;
				}													
				cursor(x, ++y);
			}
		}
		PrintEnemyHP(enemy);
		PrintEnemyStatus(enemy);
		
		/* Убрать окно сообщения */
		Sleep(2500);
		HideMenuBox(x = (WIDTH-width-6), y = ENEMY_H+3, width, height);
				
		if(enemy.hp > 0){
			mciSendString("play sounds\\ring.mp3", NULL, 0, NULL);
			s = "Enemy's Turn";
			DrawMenuBox(x = (WIDTH-s.length()-11), y = ENEMY_H+3, s.length()+6, 3);
			cursor(x+4, y+2);
			color(12);
			cout << s;			
			Sleep(3000);
			HideMenuBox(x, y, s.length()+6, 3);
			EnemyTurn(enemy);
		}
		if(enemy.hp <= 0){
			mciSendString("play sounds\\ring.mp3", NULL, 0, NULL);
			s = enemy.name + " is defeated!";
			DrawMenuBox(x = (WIDTH-s.length()-8), y = ENEMY_H+3, s.length()+2, 1);
			cursor(x+2, y+1);
			color(12);
			cout << s;
			Sleep(3000);
			HideMenuBox(x, y, s.length()+2, 1);
			HideMenuBox(WIDTH-ENEMY_W-3, 0, ENEMY_W-2, ENEMY_H-1);
			break;
		}
	}
	HideDescriptionBox(AbilityCode);
	DrawAbilityBox(AbilityCode, hero.ability[AbilityCode].name, 8);
	mciSendString("stop music\\Division.mp3", NULL, 0, NULL);
	mciSendString("resume music\\Lord_of_the_Land.mp3", NULL, 0, NULL);
	return Next;
}
