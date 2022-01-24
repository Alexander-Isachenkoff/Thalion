#include "abilitiesnav.h"
#include "globals.h"
#include "structures.h"
#include "parameters.h"
#include <iostream>
#include <conio.h>
#include <cctype>
#include <cmath>

/* Нарисовать рамку способностей*/
void DrawAbilityBox(unsigned int AbilityCode, string head, unsigned int color){
	unsigned int x, y, j;	
	unsigned int HUDx = 1 + AbilityCode*(ABILITY_W+2);
	unsigned int HUDy = (HEIGHT+HERO_H+4)/2-1;
	string buffer;
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | color));
	
	/* Верхняя граница окна */
	cursor(x = HUDx, y = HUDy);
	buffer += (char)201;
	for(j=1; j <= ABILITY_W; j++) buffer += (char)205;
	buffer += (char)187;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	
	/* Область окна */
	cursor(x, ++y);
	buffer += (char)186;
	for(j=1; j<=ABILITY_W; j++) buffer += ' ';		
	buffer += (char)186;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	cursor(x, ++y);
	
	/* Нижняя граница */
	buffer += (char)200;
	for(j=1; j <= ABILITY_W; j++) buffer += (char)205;
	buffer += (char)188;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	
	/* Заголовок */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | color));
	if(head.length() > ABILITY_W/2) cursor(x = HUDx+1, y = HUDy+1);
	else
	cursor(x = HUDx+ceilf((float)(ABILITY_W-head.length())/2), y = HUDy+1);
	fputs(head.c_str(), stdout);
}

/* Нарисовать рамку описания*/
void DrawDescriptionBox(unsigned int AbilityCode, unsigned int height){
	unsigned int x, y, i, j;
	unsigned int HUDx = 1 + AbilityCode*(ABILITY_W+2);
	unsigned int HUDy = (HEIGHT+HERO_H+4)/2+2;
	string buffer;
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	
	/* Область окна */
	cursor(x = HUDx, y = HUDy);
	for(i=1; i<=height; i++){
		buffer += (char)179;
		for(j=1; j<=ABILITY_W; j++)	buffer += ' ';
		buffer += (char)179;
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		cursor(x, ++y);
	}
	
	/* Нижняя граница */
	buffer += (char)192;
	for(j=1; j <= ABILITY_W; j++) buffer += (char)196;
	buffer += (char)217;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
}

/* Вывести описание способности */
void ShowAbilityDescription(unsigned int AbilityCode){
	unsigned int k = 0, j;
	unsigned int x = 1 + AbilityCode*(ABILITY_W+2);
	unsigned int y = (HEIGHT+HERO_H+4)/2+2;
	while(hero.ability[AbilityCode].description[k] != "0") k++;
	DrawDescriptionBox(AbilityCode, k);
	cursor(x+=2, y);
	k = 0;
	while(hero.ability[AbilityCode].description[k] != "0"){
		for(j=0; j<=hero.ability[AbilityCode].description[k].length()-1; j++){
			if(isalpha(hero.ability[AbilityCode].description[k][j]) && (hero.ability[AbilityCode].description[k][j]!='x')) color(8);
			if(hero.ability[AbilityCode].description[k][j] == '+') color(10);
			if(hero.ability[AbilityCode].description[k][j] == '-') color(12);
			if(hero.ability[AbilityCode].description[k][j] == ' ') color(7);
			putch(hero.ability[AbilityCode].description[k][j]);
		}
		k++;
		cursor(x, ++y);
	}	
}

/* Скрыть описание способностей */
void HideDescriptionBox(unsigned int AbilityCode){
	unsigned int k = 0, j, x, y;
	unsigned int HUDx = 1 + AbilityCode*(ABILITY_W+2);
	unsigned int HUDy = (HEIGHT+HERO_H+4)/2+2;
	string buffer;
	cursor(x = HUDx, y = HUDy);
	for(j=0; j<=4; j++){
		for(k=0; k<=ABILITY_W+1; k++){
			buffer += ' ';
		}
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		cursor(x, ++y);
	}
}

/* Установить способность */
void SelectAbility(unsigned int AbilityCode){
	mciSendString("stop sounds\\select2.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select2.mp3", NULL, 0, NULL);
	DrawAbilityBox(AbilityCode, hero.ability[AbilityCode].name, 15);
	ShowAbilityDescription(AbilityCode);
}

/* Переключить способность вправо */
void SelectAbilityRight(unsigned int &AbilityCode){
	HideDescriptionBox(AbilityCode);
	DrawAbilityBox(AbilityCode, hero.ability[AbilityCode].name, 8);
	SelectAbility(++AbilityCode);
}

/* Переключить способность влево */
void SelectAbilityLeft(unsigned int &AbilityCode){	
	HideDescriptionBox(AbilityCode);
	DrawAbilityBox(AbilityCode, hero.ability[AbilityCode].name, 8);
	SelectAbility(--AbilityCode);
}

/* Переключение способностей */
int AbilityNavigation(unsigned int &AbilityCode){
	char ch = 0;
	while((ch!=32) && (ch!=13)){
		ch = getch();
		switch(ch){
			case 77:
				if(AbilityCode<3) SelectAbilityRight(AbilityCode);
				break;
			case 75:
				if(AbilityCode>0) SelectAbilityLeft(AbilityCode);
				break;
			case 27: return Back;	
		}		
	}
	return Next;
}
