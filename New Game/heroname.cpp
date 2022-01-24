#include "heroname.h"
#include "globals.h"
#include "mainmenu.h"
#include "parameters.h"
#include "choosehero.h"
#include "game.h"
#include <string>
#include <conio.h>
#include <iostream>

/* ¬вод имени */
int HeroName(){
	int i = 0, x, y;
	char ch, name[17];
	string HeroName = "Hero Name:";
	int width = 17;
	int height = 3;
	x = WIDTH/2-width/2-1;
	y = HEIGHT/2-height/2;
	DrawInputBox(x, y, width, height);
	cursor(x+2,++y);
	cout << HeroName;
	cursor(x+2,y+=2);
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = TRUE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	while((ch != 13)||(i==0)){
		ch = getch();
		if(ch == 27){
			mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
			mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
			structCursorInfo.bVisible = FALSE;
			SetConsoleCursorInfo(handle, &structCursorInfo);
			return Back;
		}
		if((ch == 13) && (i>0))break;
		if(ch != 8){
			if((i < width-2) && (isalnum(ch))){
			cout << (name[i++] = ch);			
			}
		}
		else{
			if(i > 0){
				name[--i] = 0;
				cout << ch <<' '<< ch;
			}			
		}
	}
	name[i] = '\0';
	hero.name = name;
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	return Play;	
}
