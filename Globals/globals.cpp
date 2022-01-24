#include "globals.h"

/* Интерфейс */
extern const unsigned int HERO_W = 22;
extern const unsigned int HERO_NAME = 15;
extern const unsigned int HERO_H = 13;
extern const unsigned int ENEMY_W = 23;
extern const unsigned int ENEMY_H = 13;
extern const unsigned int ABILITY_W = 17;
extern const unsigned int ROOM_W = 45;
extern const unsigned int ROOM_H = 7;
unsigned int WIDTH = 128;
unsigned int HEIGHT = 33;

/* Карта */
extern const unsigned int MapSizeX = 13;
extern const unsigned int MapSizeY = 9;
extern const unsigned int StartX = MapSizeX/2;
extern const unsigned int StartY = MapSizeY/2;
unsigned int RoomQuantity;
unsigned int MaxRoomQuantity;

unsigned int ClassesQuantity = 0;
unsigned int ItemsQuantity = EndOfItems;

/* System */
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO structCursorInfo;
CONSOLE_FONT_INFOEX fontInfo;
COORD position;
