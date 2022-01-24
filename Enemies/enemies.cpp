#include "enemies.h"
#include "structures.h"
#include "globals.h"

void SetEnemiesStats(){
	int EnemyID;
	
	/* Летучая мышь */
	EnemyID = Bat;
	Enemies[EnemyID].name = "Bat";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 2;
	Enemies[EnemyID].minDmg = 1;
	Enemies[EnemyID].maxDmg = 1;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.3;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0;
	
	/* Крыса */
	EnemyID = Rat;
	Enemies[EnemyID].name = "Rat";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 3;
	Enemies[EnemyID].minDmg = 1;
	Enemies[EnemyID].maxDmg = 2;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.1;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0.2;
	Enemies[EnemyID].stunResist = 0;
	
	/* слизь */
	EnemyID = Spider;
	Enemies[EnemyID].name = "Slime";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 5;
	Enemies[EnemyID].minDmg = 1;
	Enemies[EnemyID].maxDmg = 2;
	Enemies[EnemyID].acc = 0.6;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0;
	Enemies[EnemyID].def = 0.2;
	Enemies[EnemyID].bleedingResist = 0.1;
	Enemies[EnemyID].poisonResist = 0.5;
	Enemies[EnemyID].stunResist = 0.5;
	
	/* Паук */
	EnemyID = Slime;
	Enemies[EnemyID].name = "Spider";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 5;
	Enemies[EnemyID].minDmg = 2;
	Enemies[EnemyID].maxDmg = 3;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0.05;
	Enemies[EnemyID].dodge = 0.15;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0.3;
	Enemies[EnemyID].stunResist = 0;
	
	/* Змея */
	EnemyID = Snake;
	Enemies[EnemyID].name = "Snake";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 6;
	Enemies[EnemyID].minDmg = 2;
	Enemies[EnemyID].maxDmg = 2;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0.05;
	Enemies[EnemyID].dodge = 0.15;
	Enemies[EnemyID].def = 0.15;
	Enemies[EnemyID].bleedingResist = 0.2;
	Enemies[EnemyID].poisonResist = 0.3;
	Enemies[EnemyID].stunResist = 0;
	
	/* Призрак */
	EnemyID = Ghost;
	Enemies[EnemyID].name = "Ghost";
	Enemies[EnemyID].type = "Spirit";
	Enemies[EnemyID].hp = 10;
	Enemies[EnemyID].minDmg = 1;
	Enemies[EnemyID].maxDmg = 1;
	Enemies[EnemyID].acc = 0.9;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.2;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0.1;
	
	/* Гаргулья */
	EnemyID = Gargoyle;
	Enemies[EnemyID].name = "Gargoyle";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 12;
	Enemies[EnemyID].minDmg = 2;
	Enemies[EnemyID].maxDmg = 3;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0;
	Enemies[EnemyID].def = 0.3;
	Enemies[EnemyID].bleedingResist = 0.5;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0.5;
	
	/* Гоблин */
	EnemyID = Goblin;
	Enemies[EnemyID].name = "Goblin";
	Enemies[EnemyID].type = "Creature";
	Enemies[EnemyID].hp = 8;
	Enemies[EnemyID].minDmg = 3;
	Enemies[EnemyID].maxDmg = 3;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0.1;
	Enemies[EnemyID].dodge = 0.15;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0;

	/* Скелет */
	EnemyID = Skeleton;
	Enemies[EnemyID].name = "Skeleton";
	Enemies[EnemyID].type = "Undead";
	Enemies[EnemyID].hp = 8;
	Enemies[EnemyID].minDmg = 3;
	Enemies[EnemyID].maxDmg = 4;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.1;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0;

	/* Гуль */
	EnemyID = Ghoul;
	Enemies[EnemyID].name = "Ghoul";
	Enemies[EnemyID].type = "Creature";
	Enemies[EnemyID].hp = 12;
	Enemies[EnemyID].minDmg = 4;
	Enemies[EnemyID].maxDmg = 4;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0.1;
	Enemies[EnemyID].dodge = 0.1;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 1;
	Enemies[EnemyID].stunResist = 0;
	
	/* Фантом */
	EnemyID = Phantom;
	Enemies[EnemyID].name = "Phantom";
	Enemies[EnemyID].type = "Spirit";
	Enemies[EnemyID].hp = 15;
	Enemies[EnemyID].minDmg = 3;
	Enemies[EnemyID].maxDmg = 3;
	Enemies[EnemyID].acc = 0.9;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.25;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0.1;
	
	/* Зомби-рыцарь */
	EnemyID = Zombie_Knight;
	Enemies[EnemyID].name = "Zombie-Knight";
	Enemies[EnemyID].type = "Undead";
	Enemies[EnemyID].hp = 15;
	Enemies[EnemyID].minDmg = 4;
	Enemies[EnemyID].maxDmg = 5;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.15;
	Enemies[EnemyID].def = 0.2;
	Enemies[EnemyID].bleedingResist = 0.2;
	Enemies[EnemyID].poisonResist = 0.2;
	Enemies[EnemyID].stunResist = 0;
	
	/* Король скелетов */
	EnemyID = Skeleton_King;
	Enemies[EnemyID].name = "Skeleton-King";
	Enemies[EnemyID].type = "Undead";
	Enemies[EnemyID].hp = 20;
	Enemies[EnemyID].minDmg = 5;
	Enemies[EnemyID].maxDmg = 6;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0.05;
	Enemies[EnemyID].dodge = 0.15;
	Enemies[EnemyID].def = 0.20;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0.1;
	Enemies[EnemyID].stunResist = 0.1;
	
	/* Огр */
	EnemyID = Ogre;
	Enemies[EnemyID].name = "Ogre";
	Enemies[EnemyID].type = "Creature";
	Enemies[EnemyID].hp = 25;
	Enemies[EnemyID].minDmg = 5;
	Enemies[EnemyID].maxDmg = 5;
	Enemies[EnemyID].acc = 0.5;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0.8;
	
	/* Демон */
	EnemyID = Demon;
	Enemies[EnemyID].name = "Demon";
	Enemies[EnemyID].type = "Creature";
	Enemies[EnemyID].hp = 18;
	Enemies[EnemyID].minDmg = 6;
	Enemies[EnemyID].maxDmg = 7;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.3;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0.15;
	
	/* Цербер */
	EnemyID = Cerber;
	Enemies[EnemyID].name = "Cerber";
	Enemies[EnemyID].type = "Beast";
	Enemies[EnemyID].hp = 20;
	Enemies[EnemyID].minDmg = 6;
	Enemies[EnemyID].maxDmg = 6;
	Enemies[EnemyID].acc = 0.85;
	Enemies[EnemyID].crit = 0.1;
	Enemies[EnemyID].dodge = 0.4;
	Enemies[EnemyID].def = 0.1;
	Enemies[EnemyID].bleedingResist = 0;
	Enemies[EnemyID].poisonResist = 0.1;
	Enemies[EnemyID].stunResist = 0;
	
	/* Тёмный рыцарь */
	EnemyID = Dark_Knight;
	Enemies[EnemyID].name = "Dark Knight";
	Enemies[EnemyID].type = "Spirit";
	Enemies[EnemyID].hp = 20;
	Enemies[EnemyID].minDmg = 5;
	Enemies[EnemyID].maxDmg = 6;
	Enemies[EnemyID].acc = 0.9;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.5;
	Enemies[EnemyID].def = 0;
	Enemies[EnemyID].bleedingResist = 1;
	Enemies[EnemyID].poisonResist = 0;
	Enemies[EnemyID].stunResist = 0;
	
	/* Рыцарь смерти */
	EnemyID = Death_Knight;
	Enemies[EnemyID].name = "Death Knight";
	Enemies[EnemyID].type = "Undead";
	Enemies[EnemyID].hp = 25;
	Enemies[EnemyID].minDmg = 6;
	Enemies[EnemyID].maxDmg = 8;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0.05;
	Enemies[EnemyID].dodge = 0.05;
	Enemies[EnemyID].def = 0.40;
	Enemies[EnemyID].bleedingResist = 0.1;
	Enemies[EnemyID].poisonResist = 0.1;
	Enemies[EnemyID].stunResist = 0;
	
	/* Мимик */
	EnemyID = Mimic;
	Enemies[EnemyID].name = "Mimic";
	Enemies[EnemyID].type = "Creature";
	Enemies[EnemyID].hp = 10;
	Enemies[EnemyID].minDmg = 2;
	Enemies[EnemyID].maxDmg = 3;
	Enemies[EnemyID].acc = 0.7;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0;
	Enemies[EnemyID].def = 0.25;
	Enemies[EnemyID].bleedingResist = 0.1;
	Enemies[EnemyID].poisonResist = 0.1;
	Enemies[EnemyID].stunResist = 0.1;

	/* Тёмный Лорд */
	EnemyID = The_Dark_Lord;
	Enemies[EnemyID].name = "The Dark Lord";
	Enemies[EnemyID].type = "Unknown";
	Enemies[EnemyID].hp = 50;
	Enemies[EnemyID].minDmg = 4;
	Enemies[EnemyID].maxDmg = 8;
	Enemies[EnemyID].acc = 0.8;
	Enemies[EnemyID].crit = 0;
	Enemies[EnemyID].dodge = 0.2;
	Enemies[EnemyID].def = 0.2;
	Enemies[EnemyID].bleedingResist = 0.25;
	Enemies[EnemyID].poisonResist = 0.25;
	Enemies[EnemyID].stunResist = 0.25;
}
