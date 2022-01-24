#include "choosehero.h"
#include "heroname.h"
#include "globals.h"
#include "parameters.h"
#include "mainmenu.h"
#include "navigation.h"
#include "drawings.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <string>

/* Смена героев */
void SelectHero(unsigned int x, unsigned int y, unsigned int width, unsigned int i){
	unsigned int j, k, menuX = x, menuY = y;
	
	/* Очистить поле класса */
	cursor(x+1, y = menuY+1);
	for(j=1; j<=width; j++) cout << ' ';
	
	/* Вывести класс героя */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	cursor(menuX+2, y);
	fputs("<<", stdout);
	cursor(menuX+width-2, y);
	fputs(">>", stdout);
	cursor(x=menuX+(width-Heroes[i].type.length())/2+1, y);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs(Heroes[i].type.c_str(), stdout);
	
	/* Вывод полос характеристик */
	cursor(x = menuX + 11, y += 2);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	for(j=0; j<Heroes[i].maxhp/5; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	cursor(x, ++y);
	for(j=0; j<(Heroes[i].maxDmg+Heroes[i].minDmg)/2; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	cursor(x, ++y);
	for(j=0; j<Heroes[i].acc*10; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	cursor(x, ++y);
	for(j=0; j<Heroes[i].crit*40; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	cursor(x, ++y);
	for(j=0; j<Heroes[i].dodge*20; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	cursor(x, ++y);
	for(j=0; j<Heroes[i].def*20; j++) cout << char(254);
	for(; j<10; j++) cout << ' ';
	
	/* Вывод способностей */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	cursor(x=menuX+2, y+=3);
	for(j=0; j<4; j++){
		cout << j+1 <<'.'<< Heroes[i].ability[j].name;
		for(k=Heroes[i].ability[j].name.length(); k<width-4; k++) cout << ' ';
		cursor(x, ++y);
	}
}

/* Выбор героя */
int ChooseHero(unsigned int size, unsigned int &HeroID){
	
	/* Переменные */
	unsigned int x, y, menuX, menuY, width = 21, height = 17, j;
	char ch = 0;
	string menu[]{{"Accept"},{"Cancel"}};
	x = menuX = (WIDTH-width)/2;
	y = menuY = (HEIGHT-height)/2;
	
	/* Вывести окно под выбор */
	DrawMenuBox(menuX, menuY, width, height);
	SelectHero(menuX, menuY, width, HeroID);
	/* Расставить поля */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	x += 2; y += 2;
	cursor(x, ++y);
	fputs("HP       ", stdout);
	cursor(x, ++y);
	fputs("Damage   ", stdout);
	cursor(x, ++y);
	fputs("Accuracy ", stdout);
	cursor(x, ++y);
	fputs("Crit     ", stdout);
	cursor(x, ++y);
	fputs("Dodge    ", stdout);
	cursor(x, ++y);
	fputs("Defence  ", stdout);
	cursor(x, y+=2);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	fputs("Abilities:", stdout);
	
	ShowMenuPoints(x=menuX+(width-menu[0].length())/2+1, y = menuY+height-1, menu, sizeof(menu)/sizeof(string), 0);
	SelectString(x, y, menu, j = 0, 0);
	/* Смена героев */
	j = 0;	
	while((ch != 32) && (ch != 13)){
		ch = getch();
		switch(ch){
			case 75:
				if(HeroID>0){
					mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
					mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
					SelectHero(menuX, menuY, width, --HeroID);
				}							
				break;
			case 77:
				if(HeroID<size-1){
					mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
					mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
					SelectHero(menuX, menuY, width, ++HeroID);
				}				
				break;
			case 72:
				if(j>0){
					SelectUp(x, y, menu, j, 0);
					continue;
				}
				break;
			case 80:
				if(j<1){				
					SelectDown(x, y, menu, j, 0);
					continue;
				}
				break;
			case 27:
				mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
				mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
				HideMenuBox(menuX, menuY, width, height);
				DrawLogo();
				DrawHelm();
				return Back;
		}
	}
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
	switch(j){
	case 0:
		hero = Heroes[HeroID];
		while(true){
			switch(HeroName()){
				case Back: return Repeat;
				case Play: return Play;
				case Repeat: continue;
			}
		}		
	case 1:
		HideMenuBox(menuX, menuY, width, height);
		DrawLogo();
		DrawHelm();
		return Back;
	}
}
