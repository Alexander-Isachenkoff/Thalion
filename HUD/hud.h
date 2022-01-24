#ifndef hud
#define hud
#include <string>
#include "structures.h"
void PrintHeroName();
void PrintHeroClass();
void PrintHeroHP();
void PrintHeroDmg();
void PrintHeroAccuracy();
void PrintHeroCrit();
void PrintHeroDodge();
void PrintHeroDefence();
void PrintHeroGold();
void PrintHeroKeys();
void PrintEnemyName(EnemyStats);;
void PrintEnemyClass(EnemyStats);
void PrintEnemyHP(EnemyStats);
void PrintEnemyDmg(EnemyStats);
void PrintEnemyAccuracy(EnemyStats);
void PrintEnemyCrit(EnemyStats);
void PrintEnemyDodge(EnemyStats);
void PrintEnemyDefence(EnemyStats);
void PrintEnemyStatus(EnemyStats);
void PrintAllStats();
void PrintAllEnemyStats(EnemyStats);
void DrawHudBox(int, int, int, int, string);
#endif
