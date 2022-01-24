#include "help.h"
#include "parameters.h"
#include <windows.h>
#include <MMSystem.h>
#include <iostream>
#include <conio.h>

using namespace std;

void Help(){
	system("cls");
	
	color(12); cout << "\n    1. ";
	color(8); cout << "Your objective is to find "; color(14); cout << "The Dark Lord"; color(8); cout << " and defeat him.\n";
	cout << "       To get him you should go through five floors of his lair - "; color(14); cout << "Castle Thalion"; color(8); cout << ".\n\n";

	color(12); cout << "    2. ";
	color(8);
	cout << "Use \"arrows\" to move on rooms and \"space\" or \"enter\" buttons to interact with a room.\n";
	cout << "       To go up to next floor you should find an "; color(14); cout << "Exit"; color(8); cout <<" ["; color(12); cout << "X"; color(8); cout << "] and use it.\n\n";

	color(12); cout << "    3. ";
	color(8);
	cout << "Going through the Castle you can meet "; color(14); cout << "Enemies"; color(8); cout << " who will try to kill you.\n";
	color(14); cout <<"       Battles"; color(8); cout << " occur step by step: at first it's your turn, further it's enemy's turn and etc.\n";
	cout << "       You should choose one of the hero's "; color(14); cout << "Abilities"; color(8); cout << " (use \"arrows\") to apply it (use \"space\" or \"enter\").\n\n";

	color(12); cout << "    4. ";
	color(8);
	cout << "Every class of a hero and every enemy have own Charactiristics:\n";
	cout <<	"\t   " << (char)249; color (14); cout << " HP"; color(8); cout << " (Hit Points: quantity of Damage what the hero can get before he will have died);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Dmg"; color(8); cout << " (minimal and maximal Damage);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Accuracy"; color(8); cout << " (probability of hitting on an enemy);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Crit"; color(8); cout << " (probability of making a Critical Damage);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Dodge"; color(8); cout << " (probability of Dodging from enemy's attack);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Defence"; color(8); cout << " (a percentage of Damage that will be blocked when enemy's attacking).\n";
	cout << "       Hero's defence, dodge and critical chance can't be more than 50%.\n\n";
	
	color(12); cout << "    5. ";
	color(8);
	cout <<	"Every ability has several modificators from the next ones:\n";
	cout <<	"\t   " << (char)249; color (15); cout << " Mod.Acc"; color(8); cout << " (increases or decreses base hero's accuracy);\n";
	cout <<	"\t   " << (char)249; color (15); cout << " Mod.Dmg"; color(8); cout << " (increases or decreses base hero's damage);\n";
	cout <<	"\t   " << (char)249; color (15); cout << " Mod.Crit"; color(8); cout << " (increases or decreses a chance of a ctitical hit);\n";
	cout <<	"\t   " << (char)249; color (14); cout << " Stun"; color(8); cout << " (a chance of Stunning. If you stun an enemy, he will miss his next turn);\n";
	cout <<	"\t   " << (char)249; color (12); cout << " Bleeding"; color(8); cout << " (a chance of Bleeding, damage by Bleeding and quantity of turns, during which Bleeding is affecting);\n";
	cout <<	"\t   " << (char)249; color (10); cout << " Poisoning"; color(8); cout << " (a chance of Poisoning, damage by Poison and quantity of turns, during which Poison is affecting).\n";
	cout <<	"       Every enemy has a chance of a resistance to Bleeding and Poison. Try to understand who and what resistance has.\n\n";
	
	color(12); cout << "    6. ";
	color(8);
	cout <<	"Going through the floors you can find"; color(14); cout << " Gold"; color(8); cout << ", "; color(14); cout << "Keys"; color(8); cout << ", "; color(14); cout << "Health Potions"; color(8); cout << " and "; color(14); cout << "Chests";
	color(8); cout <<" ["; color(6); cout << "?"; color(8); cout << "] and "; color(14); cout << "Items"; color(8); cout << ", changing hero's\n    characteristics.\n";
	cout <<	"       There is a "; color(14); cout <<"Store"; color(8); cout <<" ["; color(14); cout << "$"; color(8); cout << "] on an every floor, where you can buy Health Potions, Keys and Items for Gold.";
	
	char select = 0;
	while((select != ' ') && (select != 13) && (select != 27)) select = getch();
	mciSendString("stop sounds\\select.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select.mp3", NULL, 0, NULL);
	system("cls");
}
