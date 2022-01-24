#include "mainmenu.h"
#include <iostream>
#include <windows.h>
#include <cstring>
#include "globals.h"
#include "parameters.h"
#include "navigation.h"
#include "drawings.h"
#include "newgame.h"
#include "structures.h"
#include "titles.h"
#include "help.h"
using namespace std;

/* Окно меню */
void DrawMenuBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height){
	unsigned int i, j;
	string buffer;
	cursor(x, y);
	/* Верхняя граница */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	buffer += (char)219;
	for(j=1; j<=width; j++){
		buffer += (char)223;	
	}
	buffer += (char)219;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	cursor(x, ++y);
	/* Пространство */
	for(i=1; i<=height; i++){
		buffer += (char)219;
		for(j=1; j<=width; j++){
			buffer += ' ';
		}
		buffer += (char)219;
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
		cout << (char)176 << (char)176;
		SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
		cursor(x, ++y);
	}
	/* Нижняя граница */
	buffer += (char)219;
	for(j=1; j<=width; j++){
		buffer += (char)220;	
	}
	buffer += (char)219;
	fputs(buffer.c_str(), stdout);
	buffer.clear();
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	cout << (char)176 << (char)176;
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	/* Нижняя тень */
	cursor(x+2, ++y);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	for(j=1; j<=width+2; j++){
		buffer += (char)176;
		fputs(buffer.c_str(), stdout);
		buffer.clear();	
	}	
}

/* Окно ввода */
void DrawInputBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height){
	unsigned int i, j;
	cursor(x, y);
	/* Верхняя граница */
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	cout << (char)219;
	for(j=1; j<=width; j++){
		cout << (char)223;	
	}
	cout << (char)219;
	cursor(x, ++y);
	/* Пространство */
	for(i=1; i<=height; i++){
		cout << (char)219;
		for(j=1; j<=width; j++){
			cout << ' ';	
		}
		cout << (char)219;
		cursor(x, ++y);
	}
	/* Нижняя граница */
	cout << (char)219;
	for(j=1; j<=width; j++){
		cout << (char)220;	
	}
	cout << (char)219;
}

/* Скрыть окно меню */
void HideMenuBox(unsigned int x, unsigned int y, unsigned int width, unsigned int height){
	unsigned int i, j;
	string buffer;
	cursor(x,y);
	for(i=1; i<=height+3; i++){
		for(j=1; j<=width+4; j++){
			buffer += ' ';
		}
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		cursor(x,++y);
	}
}

/* Вывести пункты меню */
void ShowMenuPoints(unsigned int x, unsigned int y, string *s, unsigned int size, unsigned int interval){
	unsigned int i;
	cursor(x-=2, y);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	for(i=0; i<size; i++){		
		cout <<' '<<' '<< s[i] <<' '<<' ';
		cursor(x,y+=(interval+1));
	}
}

/* Main Menu */
int MainMenu(){
	unsigned int x, y, menuX, menuY, i;
	mciSendString("play music\\Remember_The_Heroes.mp3 repeat", NULL, 0, NULL);
	mciSendStringA("setaudio music\\Remember_The_Heroes.mp3 volume to 400", NULL, 0, NULL);
	
	/* Нарисовать шлем */	
	DrawHelm();
	
	/* Написать THALION */
	DrawLogo();
	
	/* Вывести меню */
	string MainMenu[]{{"Continue"},{"New Game"},{"Help"},{"Credits"},{"Exit"}};
	unsigned int strings = sizeof(MainMenu)/sizeof(string);
	x = menuX = 20;
	y = menuY = (HEIGHT-strings*2)/1.5;
	ShowMenuPoints(x, y, MainMenu, strings, 1);
	SelectString(x, y, MainMenu, i=1, 1);
	
	/* Навигация в главном меню */
	if((Navigation(x, y, MainMenu, i, strings, 1)) == Back) return Back;
	switch(i){
		case 0: return Repeat;
		case 1:
			ShowMenuPoints(menuX, menuY, MainMenu, strings, 1);
			while(true){
				switch(NewGame()){
					case Back: return Repeat;
					case Play: return Play;
					case Repeat: continue;
				}				
			}
		case 2: Help(); return Repeat;
		case 3: MenuTitles(); return Repeat;
		case 4:	return Back;	
	}
}
