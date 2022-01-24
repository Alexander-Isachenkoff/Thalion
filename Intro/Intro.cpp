#include "parameters.h"
#include "globals.h"
#include "drawings.h"
#include <windows.h>
#include <MMSystem.h>
#include <iostream>
#include <string>

void PrintBySymbols(string s){
	unsigned int i;	
	mciSendString("play sounds\\writing.mp3 repeat", NULL, 0, NULL);
	for(i=0; i<s.length(); i++){
		cout << s[i];
		Sleep(40);
	}
	mciSendString("stop sounds\\writing.mp3", NULL, 0, NULL);
}
void Intro(){
	unsigned int y = HEIGHT/2-4;
	string s;
	mciSendString("play music\\Death_of_Kings_2.mp3", NULL, 0, NULL);
	mciSendStringA("setaudio music\\Lord_of_the_Land.mp3 volume to 100", NULL, 0, NULL);
	
	Sleep(500);
	s = "The ruin has overtaken the world.";
	cursor((WIDTH-s.length())/2, y);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Countless hordes of evil under the leadership of the dark lord filled it.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Challenge the Dark Lord in Thalion Castle to clean the world of the plague.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Welcome to Castle Thalion!";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(4000);
	mciSendString("stop music\\Death_of_Kings_2.mp3", NULL, 0, NULL);
	system("cls");
}
void Outro(){
	system("cls");
	unsigned int y = HEIGHT/2-6;
	string s;
	mciSendString("play music\\Death_of_Kings_2.mp3", NULL, 0, NULL);
	mciSendStringA("setaudio music\\Lord_of_the_Land.mp3 volume to 100", NULL, 0, NULL);
	
	Sleep(500);
	s = "The Dark Lord is defeated...";
	cursor((WIDTH-s.length())/2, y);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Evil is going away to another world without a leader.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "But you can't resist to temptation to have power.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Now you have become new Dark Lord.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Evil spirits fall at your feet.";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(1500);
	s = "Welcome to Castle Thalion!";
	cursor((WIDTH-s.length())/2, y+=2);
	PrintBySymbols(s);
	
	Sleep(4000);
	mciSendString("stop music\\Death_of_Kings_2.mp3", NULL, 0, NULL);
	system("cls");
}
