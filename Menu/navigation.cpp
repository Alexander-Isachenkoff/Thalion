#include "navigation.h"
#include "parameters.h"
#include "globals.h"
#include <conio.h>
#include <iostream>

/* Выделить строку */
void SelectString(unsigned int x, unsigned int &y, string *s, unsigned int i, unsigned int interval){
	cursor(x-2,y+=(interval+1)*i);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs("> ", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	fputs(s[i].c_str(), stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs(" <", stdout);
}

/* Выделение строки выше */
void SelectUp(unsigned int &x, unsigned int &y, string *s, unsigned int &i, unsigned int interval){
	cursor(x-2,y);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	y-=(interval+1)*i;
	cout << "  " << s[i--] << "  ";
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);	
	SelectString(x, y, s, i, interval);
}

/* Выделение строки ниже */
void SelectDown(unsigned int &x, unsigned int &y, string *s, unsigned int &i, unsigned int interval){
	cursor(x-2,y);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	y-=(interval+1)*i;
	cout << "  " << s[i++] << "  ";
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
	SelectString(x, y, s, i, interval);
}

/* Навигация */
int Navigation(unsigned int x, unsigned int y, string *menu, unsigned int &i, unsigned int size, unsigned int interval){
	char select = 0;	
	while((select != ' ') && (select != 13) && (select != 27)){		
		select = getch();
		switch(select){
			case 72:
				if(i > 0){					
					SelectUp(x, y, menu, i, interval);
				}			
				break;
			case 80:
				if(i < size-1){
					SelectDown(x, y, menu, i, interval);
				}	
				break;
			case 27:
				mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
				mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
				return Back;
		}
	}
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
	return Next;
}
