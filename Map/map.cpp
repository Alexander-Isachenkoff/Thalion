#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include "map.h"
#include "mapnavigation.h"
#include "globals.h"
#include "structures.h"
#include "parameters.h"
using namespace std;

enum {Up, Down, Left, Right}; // ����������� ���������

/* ������ ����� */
void HideMap(){
	unsigned int i, j;
	unsigned int x = HERO_W+3;
	unsigned int y = 0;
	cursor(x,y);
	for(i=1; i<=MapSizeY*2+3; i++){
		for(j=1; j<=WIDTH-ENEMY_W-HERO_W-6; j++){
			cout << ' ';
		}
		cursor(x,++y);
	}
}

/* ��������� ������ */
void GenerateRoom(unsigned int x, unsigned int y){
	while(RoomQuantity != MaxRoomQuantity){
		switch(rand() % 4){
			case Up:
				if((y>0) && !((Map[x-1][y].room)&&(Map[x-1][y-1].room)) && !((Map[x+1][y].room)&&(Map[x+1][y-1].room))){
					if(!Map[x][y-1].room){
						Map[x][y-1].room = true;
						RoomQuantity++;
					}
					GenerateRoom(x, y-1);
				}
				break;
			case Down:
				if((y<MapSizeY-1) && !((Map[x-1][y].room)&&(Map[x-1][y+1].room)) && !((Map[x+1][y].room)&&(Map[x+1][y+1].room))){
					if(!Map[x][y+1].room){
						Map[x][y+1].room = true;
						RoomQuantity++;
					}
					GenerateRoom(x, y+1);
				}
				break;			
			case Left:
				if((x>0) && !((Map[x][y+1].room)&&(Map[x-1][y+1].room)) && !((Map[x][y-1].room)&&(Map[x-1][y-1].room))){
					if(!Map[x-1][y].room){
						Map[x-1][y].room = true;
						RoomQuantity++;
					}
					GenerateRoom(x-1, y);
				}
				break;			
			case Right:
				if((x<MapSizeX-1) && !((Map[x][y+1].room)&&(Map[x+1][y+1].room)) && !((Map[x][y-1].room)&&(Map[x+1][y-1].room))){
					if(!Map[x+1][y].room){
						Map[x+1][y].room = true;
						RoomQuantity++;
					}
					GenerateRoom(x+1, y);
				}
				break;			
		}		
	}
}

/* ��������� ����� */
void GenerateMap(){
	typedef MAP* RoomPointer;
	MAP **SpecialRooms;	
	unsigned int x, y, i, DeadEnd = 0;

	while(DeadEnd < 4){
		srand(time(NULL));
		/* �������� ������� */
		for(y=0; y<MapSizeY; y++){
			for(x=0; x<MapSizeX; x++){
				Map[x][y].room = false;
				Map[x][y].type = Usual;
				Map[x][y].nearRooms = 0;
				Map[x][y].explored = false;
			}
		}
		RoomQuantity = 0;
		
		/* ��������� ������� */
		Map[StartX][StartY].room = true;	
		Map[StartX][StartY].type = Start;
		Map[StartX][StartY].explored = true;
		RoomQuantity++;
		
		/* ��������� ������ */	
		GenerateRoom(MapSizeX/2, MapSizeY/2);
		
		/* �������� �� ������ */
		DeadEnd = 0;
		for(y=0; y<MapSizeY; y++){
			for(x=0; x<MapSizeX; x++){
				if(Map[x][y].room){				
					if((Map[x-1][y].room) && (x>0)) Map[x][y].nearRooms++;
					if((Map[x+1][y].room) && (x<MapSizeX-1)) Map[x][y].nearRooms++;
					if((Map[x][y-1].room) && (y>0)) Map[x][y].nearRooms++;
					if((Map[x][y+1].room) && (y<MapSizeY-1)) Map[x][y].nearRooms++;
					if(Map[x][y].nearRooms == 1) DeadEnd++;
				}
			}
		}
	}
	
	/* ������ ������� ��������� ������ */
	SpecialRooms = new RoomPointer[DeadEnd];
	i = 0;
	for(y=0; y<MapSizeY; y++){
		for(x=0; x<MapSizeX; x++){
			if(Map[x][y].nearRooms == 1) SpecialRooms[i++] = &Map[x][y];
		}
	}
	
	/* ����������� ����������� ������ */
	do i = rand() % DeadEnd;
	while(SpecialRooms[i]->type == Start);
	SpecialRooms[i]->type = Store;
	do i = rand() % DeadEnd;
	while((SpecialRooms[i]->type == Store) || (SpecialRooms[i]->type == Start));
	SpecialRooms[i]->type = Exit;
	do i = rand() % DeadEnd;
	while((SpecialRooms[i]->type == Store) || (SpecialRooms[i]->type == Exit) || (SpecialRooms[i]->type == Start));
	SpecialRooms[i]->type = Treasure;
	delete [] SpecialRooms;
	
	SelectRoom(StartX, StartY);
}

/* �������� ������� */
void DrawRoom(unsigned int x, unsigned int y, unsigned int colour){
	unsigned int X=(WIDTH-MapSizeX*4)/2+(x+1)*4; 
	unsigned int Y=1+(y+1)*2;
	color(colour);
	cursor(X-2, Y-1);
	/* ������� ����� ���� */
	if(((y==0)||((y>0)&&(!Map[x][y-1].room))) && ((x>0)&&(Map[x-1][y].room)) && ((x==0)||(y==0)||((x>0)&&(y>0)&&(!Map[x-1][y-1].room)))) cout << (char)194; // ������ ����� �������
	if(((y==0)||((y>0)&&(!Map[x][y-1].room))) && ((x==0)||((x>0)&&(!Map[x-1][y].room))) && ((x==0)||(y==0)||((x>0)&&(y>0)&&(!Map[x-1][y-1].room)))) cout << (char)218; // �� ������, �� �����, �� � ����
	if(((y>0)&&(Map[x][y-1].room)) && ((x==0)||((x>0)&&(!Map[x-1][y].room))) && ((x==0)||(y==0)||((x>0)&&(y>0)&&(!Map[x-1][y-1].room)))) cout << (char)195; // ���� ������ ������� �������
	if((((y>0)&&(Map[x][y-1].room)) && ((x>0)&&(Map[x-1][y].room))) || ((x>0)&&(y>0)&&(Map[x-1][y-1].room))) cout << (char)197; // ���� ������� � ����� ��� ����� ������
	/* ���� */
	if(((y>0) && (Map[x][y-1].room))) cout << "   ";
	else cout << (char)196 << (char)196 << (char)196;
	/* ������� ������ ���� */
	if(((y==0)||((y>0)&&(!Map[x][y-1].room))) && ((x<MapSizeX-1)&&(Map[x+1][y].room)) && ((x==MapSizeX-1)||(y==0)||((x<MapSizeX-1)&&(y>0)&&(!Map[x+1][y-1].room)))) cout << (char)194; // ������ ������ �������
	if(((y==0)||((y>0)&&(!Map[x][y-1].room))) && ((x==MapSizeX-1)||((x<MapSizeX-1)&&(!Map[x+1][y].room))) && ((x==MapSizeX-1)||(y==0)||((x<MapSizeX-1)&&(y>0)&&(!Map[x+1][y-1].room)))) cout << (char)191; // �� ������, �� ������, �� � ����
	if(((y>0)&&(Map[x][y-1].room)) && ((x==MapSizeX-1)||((x<MapSizeX-1)&&(!Map[x+1][y].room))) && ((x==MapSizeX-1)||(y==0)||((x<MapSizeX-1)&&(y>0)&&(!Map[x+1][y-1].room)))) cout << (char)180; // ���� ������ ������� �������
	if((((y>0)&&(Map[x][y-1].room)) && ((x<MapSizeX-1)&&(Map[x+1][y].room))) || ((x<MapSizeX-1)&&(y>0)&&(Map[x+1][y-1].room))) cout << (char)197; // ���� ������� � ����� ��� ����� ������				
	/* ����� */
	cursor(X-2, Y);
	if((x>0) && (Map[x-1][y].room)) cout << ' ';
	else cout << (char)179;
	cout << ' ';
	if(Map[x][y].type == Usual) cout << ' ';
	if(Map[x][y].type == Start) cout << ' ';
	color(14);
	if(Map[x][y].type == Store) cout << '$';
	color(12);
	if(Map[x][y].type == Exit) cout << 'X';
	color(6);
	if(Map[x][y].type == Treasure) cout << (char)15;
	cout << ' ';
	color(colour);
	if((x<MapSizeX-1) && (Map[x+1][y].room)) cout << ' ';
	else cout << (char)179;
	/* ������ ����� ���� */
	cursor(X-2, Y+1);
	if(((y==MapSizeY-1)||((y<MapSizeY-1)&&(!Map[x][y+1].room))) && ((x>0)&&(Map[x-1][y].room)) && ((x==0)||(y==MapSizeY-1)||((x>0)&&(y<MapSizeY-1)&&(!Map[x-1][y+1].room)))) cout << (char)193; // ������ ����� �������
	if(((y==MapSizeY-1)||((y<MapSizeY-1)&&(!Map[x][y+1].room))) && ((x==0)||((x>0)&&(!Map[x-1][y].room))) && ((x==0)||(y==MapSizeY-1)||((x>0)&&(y<MapSizeY-1)&&(!Map[x-1][y+1].room)))) cout << (char)192; // �� �����, �� �����, �� � ����
	if(((y<MapSizeY-1)&&(Map[x][y+1].room)) && ((x==0)||((x>0)&&(!Map[x-1][y].room))) && ((x==0)||(y==MapSizeY-1)||((x>0)&&(y<MapSizeY-1)&&(!Map[x-1][y+1].room)))) cout << (char)195; // ���� ������ ������ �������
	if((((y<MapSizeY-1)&&(Map[x][y+1].room)) && ((x>0)&&(Map[x-1][y].room))) || ((x>0)&&(y<MapSizeY-1)&&(Map[x-1][y+1].room))) cout << (char)197; // ���� ������ � ����� ��� ����� �����					
	/* ��� */
	if(((y<MapSizeY-1) && (Map[x][y+1].room))) cout << "   ";
	else cout << (char)196 << (char)196 << (char)196;
	/* ������ ������ ���� */
	if(((y==MapSizeY-1)||((y<MapSizeY-1)&&(!Map[x][y+1].room))) && ((x<MapSizeX-1)&&(Map[x+1][y].room)) && ((x==MapSizeX-1)||(y==MapSizeY-1)||((x<MapSizeX-1)&&(y<MapSizeY-1)&&(!Map[x+1][y+1].room)))) cout << (char)193; // ������ ������ �������
	if(((y==MapSizeY-1)||((y<MapSizeY-1)&&(!Map[x][y+1].room))) && ((x==MapSizeX-1)||((x<MapSizeX-1)&&(!Map[x+1][y].room))) && ((x==MapSizeX-1)||(y==MapSizeY-1)||((x<MapSizeX-1)&&(y<MapSizeY-1)&&(!Map[x+1][y+1].room)))) cout << (char)217; // �� �����, �� ������, �� � ����
	if(((y<MapSizeY-1)&&(Map[x][y+1].room)) && ((x==MapSizeX-1)||((x<MapSizeX-1)&&(!Map[x+1][y].room))) && ((x==MapSizeX-1)||(y==MapSizeY-1)||((x<MapSizeX-1)&&(y<MapSizeY-1)&&(!Map[x+1][y+1].room)))) cout << (char)180; // ������ ������ �������
	if((((y<MapSizeY-1)&&(Map[x][y+1].room)) && ((x<MapSizeX-1)&&(Map[x+1][y].room))) || ((x<MapSizeX-1)&&(y<MapSizeY-1)&&(Map[x+1][y+1].room))) cout << (char)197; // ���� ������ � ������ ��� ������ �����						
}

