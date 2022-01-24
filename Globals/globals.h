#ifndef globals
#define globals
#include <windows.h>
#include "structures.h"

/* Интерфейс */
extern const unsigned int HERO_W;
extern const unsigned int HERO_NAME;
extern const unsigned int HERO_H;
extern const unsigned int ENEMY_W;
extern const unsigned int ENEMY_H;
extern const unsigned int ABILITY_W;
extern const unsigned int ROOM_W;
extern const unsigned int ROOM_H;
extern unsigned int WIDTH;
extern unsigned int HEIGHT;
extern unsigned int ClassesQuantity;

enum{Repeat, Back, Play, Next, ChestOpening, Buying, Exiting, Move, Nothing};

/* Карта */
extern unsigned int RoomQuantity;
extern unsigned int MaxRoomQuantity;
extern const unsigned int MapSizeX;
extern const unsigned int MapSizeY;
extern const unsigned int StartX;
extern const unsigned int StartY;

enum {Usual, Store, Start, Treasure, Exit}; // Типы комнат

/* Враги */
enum {
	Bat,
	Gargoyle,
	Ghost,
	Ghoul,
	Mimic,
	Phantom,
	Skeleton,
	Skeleton_King,
	Slime,
	Spider,
	Rat,
	Goblin,
	Snake,
	Zombie_Knight,
	Dark_Knight,
	Cerber,
	Ogre,
	Demon,
	Death_Knight,
	The_Dark_Lord
};

/* Предметы */
enum {
	Health,
	Key,
	Health_Stone,
	Accuracy_Stone,
	Bleed_Stone,
	Poison_Stone,
	Damage_Stone,
	Dodge_Stone,
	Critical_Stone,
	Protection_Stone,
	Stun_Stone,
	Health_Amulet,
	Accuracy_Amulet,
	Bleed_Amulet,
	Poison_Amulet,
	Damage_Amulet,
	Dodge_Amulet,
	Critical_Amulet,
	Protection_Amulet,
	Stun_Amulet,
	Mystery_Ring1,
	Mystery_Ring2,
	Mystery_Ring3,
	Mystery_Ring4,
	Mystery_Ring5,
	Leather_Helm,
	Leather_Armor,
	Leather_Gloves,
	Leather_Pants,
	Leather_Boots,
	Heavy_Helm,
	Heavy_Armor,
	Heavy_Gloves,
	Heavy_Pants,
	Heavy_Boots,
	Old_Cloak,
	Good_Cloak,
	Luxurious_Cloak,
	Steel_Sword,
	Battle_Axe,
	Balanced_Sword,
	Light_Dagger,
	EndOfItems,
};

/* System */
extern HANDLE handle;
extern CONSOLE_CURSOR_INFO structCursorInfo;
extern CONSOLE_FONT_INFOEX fontInfo;
extern COORD position;
#endif
