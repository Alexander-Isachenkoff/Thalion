#include "game.h"
#include "hud.h"
#include "drawings.h"
#include "structures.h"
#include "globals.h"
#include "abilitiesnav.h"
#include "battle.h"
#include "map.h"
#include "mapnavigation.h"
#include "parameters.h"
#include "mainmenu.h"
#include "items.h"
#include "store.h"
#include "titles.h"
#include "intro.h"
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstdlib>
using namespace std;

enum {Gold, Chest, Item}Loot;

/* Смерть героя */
void HeroDeath(){
	unsigned int x, y, width;
	char ch;
	string s;
	system("cls");
	mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL);
	mciSendString("play music\\Death_of_Kings_2.mp3 repeat", NULL, 0, NULL);
	DrawGameOver();
	s = " DEAD!";
	DrawMenuBox(x = (WIDTH-(HERO_NAME+s.length()+6))/2, y = (HEIGHT-7)/2, width = HERO_NAME+s.length()+6, 5);
	cursor(x+4+(width-6-(hero.name.length()+s.length()))/2, y+=2);
	color(8);
	cout << hero.name;
	color(12);
	cout << s;
	s = "Main Menu";
	cursor(x+(width-s.length())/2-1, y+=2);
	color(12);
	cout << "> ";
	color(15);
	cout << s;
	color(12);
	cout << " <";
	while((ch != 13) && (ch != 32)){
		ch = getch();
	}
	mciSendString("stop music\\Death_of_Kings_2.mp3", NULL, 0, NULL);
	system("cls");
}

/* Очистить статус комнаты */
void CleanRoomStatus(){
	unsigned int i, j;
	unsigned int x = WIDTH-ROOM_W-2;
	unsigned int y = (HEIGHT+HERO_H+4)/2+2;
	string buffer;
	cursor(x,y);
	for(i=1; i<=ROOM_H-2; i++){
		for(j=1; j<=ROOM_W-2; j++){
			buffer += ' ';
		}
		fputs(buffer.c_str(), stdout);
		buffer.clear();
		cursor(x,++y);
	}
}

/* Вывести статус комнаты */
void PrintRoomStatus(unsigned int x, unsigned int y){
	unsigned int X, Y;
	cursor(X = WIDTH-ROOM_W-1, Y = (HEIGHT+HERO_H+4)/2+2);			
	switch(Map[x][y].type){
		case Start:
		case Usual:
			color(7);
			fputs("Empty room.", stdout);
			cursor(X, ++Y);
			fputs("There is nothing interesting here...", stdout);
			break;				
		case Store:
			color(7); cout << "This is a ";
			color(14); cout << "Store"; color(7); cout << ".";
			cursor(X, ++Y);
			color(7); cout << "Press \"space\" or \"enter\" to interact.";
			break;
		case Treasure:
			color(7); cout << "There is a ";
			color(14); cout << "Treasure";
			color(7); cout << "!";
			cursor(X, ++Y);
			color(7); cout << "Press \"space\" or \"enter\" to open a chest.";
			cursor(X, ++Y);	cout << "You need a ";
			color(14); cout << "Key"; color(7); cout << ".";
			break;				
		case Exit:
			color(7); cout << "There is a ";
			color(14); cout << "Stairway";
			color(7); cout << ".";
			cursor(X, ++Y);
			color(7); cout << "Press \"space\" or \"enter\" to go up.";
			break;					
	}	
}

/* Найден предмет */
void GetItem(unsigned int ItemID){
	unsigned int X, Y;
	cursor(X = WIDTH-ROOM_W-1, Y = (HEIGHT+HERO_H+4)/2+2);
	color(7); cout << "You have found ";
	color(14); cout << Items[ItemID].name; color(7); cout << "!";
	cursor(X, ++Y);
	color(9); cout << Items[ItemID].description;
	Items[ItemID].Buf();
	Items[ItemID].Debuf();
	PrintAllStats();	
}

/* Открыть сундук */
int OpenChest(int x, int y){
	unsigned int P, gold, ItemID;
	P = rand() % 100 + 1;
	/* 10% битва с мимиком */
	if((P>=1) && (P<=10)){
		CleanRoomStatus();
		cursor(WIDTH-ROOM_W-1, (HEIGHT+HERO_H+4)/2+2);
		color(7); cout << "You are attacked by ";
		color(12); cout << Enemies[Mimic].name; color(7); cout << "!";
		if(Battle(Mimic) == Back){
			return Back;
		}
		Map[x][y].type = Usual;
		CleanRoomStatus();
		PrintRoomStatus(x, y);	
		return Next;
	}
	
	mciSendString("play sounds\\chest.mp3 wait", NULL, 0, NULL);
	if((P>=11) && (P<=60)) Loot = Gold;
	if((P>=61) && (P<=100)) Loot = Item;
	
	/* Определение лута */
	CleanRoomStatus();
	switch(Loot){
		case Gold:
			gold = (rand() % 10 + 1)*5;
			cursor(WIDTH-ROOM_W-1, (HEIGHT+HERO_H+4)/2+2);
			color(7); cout << "You have found ";
			color(14); cout << gold;
			color(7); cout << " Gold!";
			hero.gold += gold;
			PrintHeroGold();
			mciSendString("play sounds\\coins2.mp3 wait", NULL, 0, NULL);	
			break;
		case Item:
			if(P<91){
				GetItem(Health);
				mciSendString("play sounds\\health.mp3 wait", NULL, 0, NULL);
				break;				
			}
			do ItemID = rand() % EndOfItems; while((ItemID == Key) || (ItemID == Health));
			GetItem(ItemID);
			mciSendString("play sounds\\jingle2.mp3 wait", NULL, 0, NULL);
			break;	
	}
	Map[x][y].type = Usual;
	return Next;
}

/* Найдена добыча */
void GetLoot(unsigned int x, unsigned int y){
	unsigned int P, gold, X, Y;
	
	/* Вероятность выпадения лута */
	P = rand() % 100 + 1;
	if((P>=1) && (P<=50)) Loot = Gold;
	if((P>=51) && (P<=80)) Loot = Item;
	if((P>=81) && (P<=100)) Loot = Chest;
	
	/* Определение лута */
	CleanRoomStatus();
	switch(Loot){
		case Gold: // Золото
			gold = (rand() % 5 + 1)*5;
			cursor(WIDTH-ROOM_W-1, (HEIGHT+HERO_H+4)/2+2);
			color(7); cout << "You have found ";
			color(14); cout << gold;
			color(7); cout << " Gold!";
			hero.gold += gold;
			PrintHeroGold();
			mciSendString("play sounds\\coins2.mp3 wait", NULL, 0, NULL);	
			break;
		case Chest: // Сундук			
			cursor(X = WIDTH-ROOM_W-1, Y = (HEIGHT+HERO_H+4)/2+2);
			color(7); cout << "You have found a";
			color(14); cout << " Treasure"; color(7); cout << "!";
			cursor(X, ++Y);
			color(7); cout << "Press \"space\" or \"enter\" to open a chest.";
			cursor(X, ++Y);	cout << "You need a ";
			color(14); cout << "Key"; color(7); cout << ".";
			Map[x][y].type = Treasure;
			mciSendString("play sounds\\jingle.mp3 wait", NULL, 0, NULL);
			break;
		case Item: // Здоровье или Ключ
			switch(P = rand() % 2){
				case 0:
					GetItem(Health);
					mciSendString("play sounds\\health.mp3 wait", NULL, 0, NULL);
					break;
				case 1:
					GetItem(Key);
					mciSendString("play sounds\\key.mp3 wait", NULL, 0, NULL);
					break;
			}
			break;					
	}
}

/* Событие в комнате */
int RoomEvent(unsigned int x, unsigned int y, unsigned int Floor[][6], unsigned int FloorID){
	unsigned int P, enemyID;
	P = rand() % 100 + 1;
	
	/* Битва */
	if((P>=1) && (P<=50)){
		enemyID = Floor[FloorID][rand() % 6];
		CleanRoomStatus();
		cursor(WIDTH-ROOM_W-1, (HEIGHT+HERO_H+4)/2+2);
		color(7); cout << "You are attacked by ";
		color(12); cout << Enemies[enemyID].name; color(7); cout << "!";
		if(Battle(enemyID) == Back){
			system("cls");
			return Back;	
		}		
	}
	if((P>=26) && (P<=80)) GetLoot(x, y); // Добыча
	else{
		CleanRoomStatus();
		PrintRoomStatus(x, y);
	}
	return Next;
}

void StartGame(){
	srand(time(NULL));
	SetItems();	
	
	/* Враги на этажах */
	unsigned int Floor[5][6]{
		{Bat, Rat, Spider, Slime, Snake, Ghost},
		{Spider, Snake, Ghost, Gargoyle, Goblin, Skeleton},
		{Gargoyle, Goblin, Skeleton, Ghoul, Phantom, Zombie_Knight},
		{Ghoul, Phantom, Zombie_Knight, Skeleton_King, Ogre, Demon},
		{Skeleton_King, Ogre, Demon, Cerber, Dark_Knight, Death_Knight}
	};	
	unsigned int i, x = MapSizeX/2, y = MapSizeY/2, FloorID, ItemID, Action, GoodsQuantity;
	
	/* Выключить музыку из меню, очистить консоль, включить музыку игры */
	mciSendString("stop music\\Remember_The_Heroes.mp3", NULL, 0, NULL);
	system("cls");
	mciSendString("play music\\Lord_of_the_Land.mp3 repeat", NULL, 0, NULL);
	mciSendStringA("setaudio music\\Lord_of_the_Land.mp3 volume to 1000", NULL, 0, NULL);
	
	/* Отрисовка интерфейса */
	hero.gold = 1000;
	hero.keys = 10;
	DrawHudBox(1, 0, HERO_W, HERO_H, "HERO");
	PrintAllStats();
	DrawHudBox(WIDTH-ROOM_W-3, (HEIGHT+HERO_H+4)/2-1, ROOM_W, ROOM_H, "ROOM");
	for(i=0; i<4; i++) DrawAbilityBox(i, hero.ability[i].name, 8); // Способности	
	
	/* Карта */
	MaxRoomQuantity = 10;
	for(FloorID = 0; FloorID<=4; FloorID++){
		HideMap();
		cursor((WIDTH-7)/2, 1);
		color(14);
		cout << "Floor " << FloorID+1;
		MaxRoomQuantity +=(rand() % 3 + 3);
		GenerateMap();
		CleanRoomStatus();
		PrintRoomStatus(x = StartX, y = StartY);
		
		/* Вещи в магазине */		
		Goods[0] = Items[Health];		
		Goods[1] = Items[Key];		
		for(i=2; i<=4; i++){		
			do ItemID = rand() % EndOfItems; while((ItemID == Key) || (ItemID == Health));
			Goods[i] = Items[ItemID];		
		}
		GoodsQuantity = 5;
		
		/* Игра */
		while(true){
			/* Определение действия на карте */
			if((Action = MapNavigation(x, y)) == Exiting){
				mciSendString("play sounds\\door.mp3 wait", NULL, 0, NULL);
				break;
			}
			switch(Action){
				case Move:
					mciSendString("stop sounds\\steps.mp3", NULL, 0, NULL);
					mciSendString("play sounds\\steps.mp3", NULL, 0, NULL);
					if((Map[x][y].type == Usual) && (!Map[x][y].explored)){
						if(RoomEvent(x, y, Floor, FloorID) == Back){
							mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL); system("cls"); return;	
						}
					}
					else{
						CleanRoomStatus();
						PrintRoomStatus(x, y);
					}
					Map[x][y].explored = true;
					break;
				case ChestOpening:
					if(hero.keys){
						hero.keys--;
						PrintHeroKeys();
						if(OpenChest(x, y) == Back){
							mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL); system("cls"); return;
						};
					}
					break;
				case Buying: Shop(Goods, GoodsQuantity); break;
				case Back: mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL); system("cls"); return;
			}			
			if(hero.hp <= 0){
				HeroDeath();
				return;
			}		
		}			
	}
	HideMap();
	if(Battle(The_Dark_Lord) == Back){
		system("cls"); return;
	}
	if(hero.hp <= 0){
		HeroDeath();
		return;
	}
	else{
		mciSendString("stop music\\Lord_of_the_Land.mp3", NULL, 0, NULL);
		Outro();
		EndTitles();
	}	
}
