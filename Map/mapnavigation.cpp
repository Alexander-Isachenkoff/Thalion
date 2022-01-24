#include "mapnavigation.h"
#include "structures.h"
#include "globals.h"
#include "parameters.h"
#include "structures.h"
#include "game.h"
#include "map.h"
#include "hud.h"
#include <iostream>
#include <conio.h>
using namespace std;

/* Показать соседние комнаты */
void DrawNearRooms(unsigned int x, unsigned int y){
	unsigned int color = 8;
	if((y>0) && (Map[x][y-1].room) && (!Map[x][y-1].explored)) DrawRoom(x, y-1, color);
	if((x>0) && (Map[x-1][y].room) && (!Map[x-1][y].explored)) DrawRoom(x-1, y, color);
	if((x<MapSizeX-1) && (Map[x+1][y].room) && (!Map[x+1][y].explored)) DrawRoom(x+1, y, color);
	if((y<MapSizeY-1) && (Map[x][y+1].room) && (!Map[x][y+1].explored)) DrawRoom(x, y+1, color);
}

/* Очистить комнату */
void CleanRoom(unsigned int x, unsigned int y){
	DrawRoom(x, y, 15);
}
/* Установить комнату */
void SelectRoom(unsigned int x, unsigned int y){
	DrawNearRooms(x, y);
	DrawRoom(x, y, 15);	
	color(10);
	cursor((WIDTH-MapSizeX*4)/2+(x+1)*4, 1+(y+1)*2);
	cout << (char)254;
}
/* Идти вверх */
void GoUp(unsigned int &x, unsigned int &y){
	CleanRoom(x, y);
	SelectRoom(x, --y);
}
/* Идти вниз */
void GoDown(unsigned int &x, unsigned int &y){
	CleanRoom(x, y);
	SelectRoom(x, ++y);
}
/* Идти влево */
void GoLeft(unsigned int &x, unsigned int &y){
	CleanRoom(x, y);
	SelectRoom(--x, y);
}
/* Идти вправо */
void GoRight(unsigned int &x, unsigned int &y){
	CleanRoom(x, y);
	SelectRoom(++x, y);
}

/* Навигация по карте */
int MapNavigation(unsigned int &x, unsigned int &y){
	switch(getch()){
		case 72:
			if((y>0) && (Map[x][y-1].room)){
				GoUp(x, y);
				return Move;	
			}
			break;
		case 75:
			if((x>0) && (Map[x-1][y].room)){
				GoLeft(x, y);
				return Move;
			}
			break;
		case 77:
			if((x<MapSizeX-1) && (Map[x+1][y].room)){
				GoRight(x, y);
				return Move;
			}
			break;
		case 80:
			if((y<MapSizeY-1) && (Map[x][y+1].room)){
				GoDown(x, y);
				return Move;			
			}
			break;
		case 32:
		case 13:
			switch(Map[x][y].type){
				case Exit:
					return Exiting;
				case Store:
					return Buying;
				case Treasure:
					return ChestOpening;
			}
		case 27: return Back;
	}
	return Nothing;		
}
