#include "datascanning.h"
#include "structures.h"
#include "parameters.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <conio.h>
using namespace std;
void AbilityDescription(Stats &hero, unsigned int AbilityCode){
	unsigned int n;
	int num;
	string mark;
	for(n=0; n<sizeof(Heroes[0].ability[0].description)/sizeof(string); n++){
		hero.ability[AbilityCode].description[n] = "0";
	}
	n = 0;
	if(hero.ability[AbilityCode].modAcc != 1){
		if(hero.ability[AbilityCode].modAcc > 1) mark = "+";
		else mark = "-";
		hero.ability[AbilityCode].description[n++] = "Mod.Acc: " + mark + to_string(num = round(fabs((hero.ability[AbilityCode].modAcc-1)*100))) + '%';
	}
	if(hero.ability[AbilityCode].modDmg != 1){
		if(hero.ability[AbilityCode].modDmg > 1) mark = "+";
		else mark = "-";
		hero.ability[AbilityCode].description[n++] = "Mod.Dmg: " + mark + to_string(num = round(fabs((hero.ability[AbilityCode].modDmg-1)*100))) + '%';
	}
	if(hero.ability[AbilityCode].modCrit != 1){
		hero.ability[AbilityCode].description[n++] = "Mod.Crit: x" + to_string(num = hero.ability[AbilityCode].modCrit) +"."+ to_string(num = ((hero.ability[AbilityCode].modCrit-(num=hero.ability[AbilityCode].modCrit))*10));
	}
	if(hero.ability[AbilityCode].stun != 0){
		hero.ability[AbilityCode].description[n++] = "Stunning: " + to_string(num = round(hero.ability[AbilityCode].stun*100)) + "%";
	}
	if(hero.ability[AbilityCode].bleedChance != 0){
		hero.ability[AbilityCode].description[n++] = "Bleeding: " + to_string(num = round(hero.ability[AbilityCode].bleedChance*100)) +"%";
		hero.ability[AbilityCode].description[n++] = to_string(hero.ability[AbilityCode].bleedDmg) + " Dmg / " + to_string(hero.ability[AbilityCode].bleedTurns) + " turns";
	}
	if(hero.ability[AbilityCode].poisonChance != 0){
		hero.ability[AbilityCode].description[n++] = "Poison: " + to_string(num = round(hero.ability[AbilityCode].poisonChance*100)) +"%";
		hero.ability[AbilityCode].description[n++] = to_string(hero.ability[AbilityCode].poisonDmg) + " Dmg / " + to_string(hero.ability[AbilityCode].poisonTurns) + " turns";
	}	
}

void DataScanning(){
	/* Переменные */
	string s;	// строка временного хранения
	ifstream heroes;
	ifstream abilities;
	unsigned int i, j;
	
	/* Открытие файла "heroes.txt" */
	heroes.open("data\\heroes.txt");
	if(!heroes){
		system("cls");
		cout << "Error! File \"heroes.txt\" is not avaiable.\nPress any button to exit...";
		getch();
		exit(1);
	}
	
	/* Подсчёт кол-ва героев */
	while(!heroes.eof()){
		heroes >> s;
		if(s == "Class:") ClassesQuantity++;
	}
	heroes.close();
	
	/* Создание массива под героев */
	Heroes = new Stats[ClassesQuantity];
		
	/* Открытие файла "heroes.txt" */
	heroes.open("data\\heroes.txt");
	if(!heroes){
		system("cls");
		cout << "Error! File \"heroes.txt\" is not avaiable.\nPress any button to exit...";
		getch();
		exit(1);
	}
	
	/* Запись героев в структуру */	
	for(i=0; i<ClassesQuantity; i++){
		while(!heroes.eof()){
			heroes >> s;
			if(s == "Class:"){
				heroes >> Heroes[i].type;
				heroes >> s >> Heroes[i].maxhp;
				Heroes[i].hp = Heroes[i].maxhp;
				heroes >> s; getline(heroes, s, '-');
				heroes >> Heroes[i].maxDmg;
				Heroes[i].minDmg = stoi(s);
				heroes >> s >> Heroes[i].acc;
				heroes >> s >> Heroes[i].crit;
				heroes >> s >> Heroes[i].dodge;
				heroes >> s >> Heroes[i].def;
				
				/* Запись способностей */
				for(j=0; j<=3; j++){
					getline(heroes, s, ':');
					getline(heroes, Heroes[i].ability[j].name);
					
					/* Открытие файла "abilities.txt" */
					abilities.open("data\\abilities.txt");
					if(!abilities){
						system("cls");
						cout << "Error! File \"abilities.txt\" is not avaiable.\nPress any button to exit...";
						getch();
						exit(1);					
					}
					
					/* Поиск способности по имени */
					while(s!=Heroes[i].ability[j].name){
						abilities >> s;
						if(s == "Name:") getline(abilities, s);
					}
					abilities >> s >> Heroes[i].ability[j].modAcc;
					abilities >> s >> Heroes[i].ability[j].modDmg;
					abilities >> s >> Heroes[i].ability[j].modCrit;
					abilities >> s >> Heroes[i].ability[j].stun;
					abilities >> s >> Heroes[i].ability[j].bleedChance >> s >> Heroes[i].ability[j].bleedDmg >> s >> Heroes[i].ability[j].bleedTurns;
					abilities >> s >> Heroes[i].ability[j].poisonChance >> s >> Heroes[i].ability[j].poisonDmg >> s >> Heroes[i].ability[j].poisonTurns;					
					/* Формирование описания способности */
					AbilityDescription(Heroes[i], j);
					abilities.close();
				}
				break;				
			}
		}
	}
	heroes.close();
}
