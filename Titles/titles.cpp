#include "titles.h"
#include "parameters.h"
#include "globals.h"
#include "drawings.h"
#include <windows.h>
#include <MMSystem.h>
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

void ShowTitles(unsigned int x, unsigned int y, bool delay){
	string s;
	
	if(delay)Sleep(500);
	s = "Game by";
	cursor(x-s.length()/2, y);
	color(14);
	cout << s;
	s = "Alexander Isachenkov";
	cursor(x-s.length()/2, ++y);
	color(15);
	cout << s;
	
	if(delay)Sleep(2000);
	s = "Programmer";
	cursor(x-s.length()/2, y+=2);
	color(14);
	cout << s;
	s = "Alexander Isachenkov";
	cursor(x-s.length()/2, ++y);
	color(15);
	cout << s;
	
	if(delay)Sleep(2000);
	s = "Music";
	cursor(x-s.length()/2, y+=2);
	color(14);
	cout << s;
	
	s = "KevinMacLeod";
	cursor(x-s.length()/2, ++y);
	color(15);
	cout << s;
	s = "Death of Kings 2 (fragment)";
	cursor(x-s.length()/2, ++y);
	color(8);
	cout << s;
	s = "Division";
	cursor(x-s.length()/2, ++y);
	color(8);
	cout << s;
	s = "Lord of the Land";
	cursor(x-s.length()/2, ++y);
	color(8);
	cout << s;
	
	if(delay)Sleep(2000);
	s = "Audionautix.com";
	cursor(x-s.length()/2, y+=2);
	color(15);
	cout << s;
	s = "Remember the Heroes";
	cursor(x-s.length()/2, ++y);
	color(8);
	cout << s;
	
	if(delay)Sleep(2000);
	s = "Ost+Front";
	cursor(x-s.length()/2, y+=2);
	color(15);
	cout << s;
	s = "Ich will alles (fragment)";
	cursor(x-s.length()/2, ++y);
	color(8);
	cout << s;
	
	if(delay)Sleep(2000);
	s = "Sounds";
	cursor(x-s.length()/2, y+=2);
	color(14);
	cout << s;
	s = "noisefx.ru";
	cursor(x-s.length()/2, ++y);
	color(15);
	cout << s;
	s = "soundjay.com";
	cursor(x-s.length()/2, ++y);
	color(15);
	cout << s;	
}

void EndTitles(){
	unsigned int i, j;
	string buffer;
	system("cls");
	mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL);
	mciSendString("play music\\Ich_will_alles.mp3", NULL, 0, NULL);
	DrawLogo();
	DrawHelm();	
	ShowTitles(30, 10, true);
	Sleep(14000);
	cursor(0, 10);
	for(i=0; i<=HEIGHT-12; i++){
		for(j=0; j<=60; j++) buffer += ' ';
		buffer += "\n";
	}
	fputs(buffer.c_str(), stdout);
}

void MenuTitles(){
	system("cls");
	DrawTower();
	ShowTitles(WIDTH/2, 5, false);
	cursor((WIDTH-8)/2, HEIGHT-2);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs("> ", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	fputs("Quit", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs(" <", stdout);
	char select = 0;
	while((select != ' ') && (select != 13) && (select != 27)) select = getch();
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
	system("cls");
}
