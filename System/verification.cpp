#include <cstring>
#include <cstdlib>
#include <fstream>
#include <conio.h>
#include <iostream>
#include <cmath>
#include "verification.h"
#include "numbers.h"
#include "globals.h"
using namespace std;
/* Функция проверки файла "heroes.txt" */
int scanheroes(char *Field, char *Class, char *abilityName){
		
	/* Переменные */
	FILE *H; // "heroes.txt"
	int l, i;
	float n;	
	int a[4];
	char s[31] = {0};
	char hField[][15]{{"Class:"},{"HP:"},{"Dmg:"},{"Accuracy:"},{"Crit:"},{"Dodge:"},{"Defence:"}}; // Поля данных
	
	/* Проверка "heroes.txt" */	
	if(((H = fopen("data\\heroes.txt","r")) == NULL)){ // Проверка на существование "heroes.txt"
		return 1;
	}	
	while(!feof(H)){
		for(i=0; i<=6; i++){
			l = 0;		
			fscanf(H, "%30s%n", s, &l);
			if(!l) return 0;
			strcpy(Field, hField[i]);
			if(!strcmp(s, hField[i])){  // Проверка на соответствие полю
				switch(i){					
					case 0: // Class:
						fscanf(H, "%30s", s);
						strcpy(Class, s);
						if(strlen(s) > (HERO_W-strlen(hField[i]))) return 41;						
						break;
					case 1: // HP:
						fscanf(H, "%30s", s);
						if(isIntNumber(s)){
							n = atoi(s);
							if((n > 0)&&(n <= 1000)){
								break;
							}
						}
						return (i+9);						
					case 2: // Dmg:
						fscanf(H, " %30[^-]-", s);
						if(isIntNumber(s)){
							n = atoi(s);
							if(n > 0){
								fscanf(H, "%30s", s);
								if(isIntNumber(s)){
									n = atoi(s);	
									if(n > 0) break;
								}
							}
						}
						return 11;
					case 3: // Acc: Crit: Dodge: Def:
					case 4:
					case 5:
					case 6:
						fscanf(H, "%30s", s);
						if(isnumber(s)){
							n = atof(s);
							if((n >= 0)&&(n <= 1)) break;
						}
						return (i+9);																												
				}				
			}
			else return (i+2);			
		}
		a[0] = a[1] = a[2] = a[3] = 0;
		for(i=0; i<=3; i++){
			fscanf(H, "%30s", s);	
			if(!strcmp(s, "Ability")){ // Проверка поля Ability
				fscanf(H, " %30[^:]:", s);
				if(isIntNumber(s)){ // Проверка номера способности на целое число
					n = atoi(s);
					if((n >= 1)&&(n <= 4)&&(n != a[0])&&(n != a[1])&&(n != a[2])&&(n != a[3])){ // Проверка номера способности на [1;4] и на уникальность
						a[i] = n;
						fscanf(H, " %30[^\n]", s);
						strcpy(abilityName, s);
						if(strlen(s) > (ABILITY_W-1)) return 42;
						continue;
					}
				}
				return 17;				
			}
			return 16;	
		}
	}
	fclose(H);
}

/* Функция проверки файла "abilities.txt" */
int scanabilities(char *Field, char *abilityName){

	/* Переменные */
	FILE *A; // "abilities.txt"
	int l, i;
	float n;	
	char s[31] = {0};
	char aField[][15]{{"Name:"},{"Mod.Accuracy:"},{"Mod.Dmg:"},{"Mod.Crit:"},{"Stunning:"},{"Bleeding:"},{"Dmg:"},{"Turns:"},{"Poison:"},{"Dmg:"},{"Turns:"}}; // Поля данных
	
	/* Проверка "abilities.txt" */
	if(((A = fopen("data\\abilities.txt","r")) == NULL)){ // Проверка на существование "abilities.txt"
		return 18;
	}
	while(!feof(A)){
		for(i=0; i<=10; i++){
			l = 0;		
			fscanf(A, "%30s%n", s, &l);
			if(!l)break;
			strcpy(Field, aField[i]);
			if(!strcmp(s, aField[i])){ // Проверка на соответствие полю
				switch(i){
					case 0:
						fscanf(A, " %30[^\n]", s);
						strcpy(abilityName, s);
						if(strlen(s) > (ABILITY_W-1)) return 42;								
						break;
					case 1:
					case 2:
					case 3:
					case 4:
					case 5:
					case 8: // Проверка дробных значений
						fscanf(A, "%30s", s);
						if(isnumber(s)){
							n = atof(s);
							if((n >= 0)&&(n < 10)) break;							
						}
						return (i+30);				
					case 6:
					case 7:
					case 9:
					case 10: // Проверка целых значений
						fscanf(A, "%30s", s);
						if(isIntNumber(s)){
							n = atoi(s);
							if(n >= 0) break;
						}
						return (i+30);
				}
			}
			else return (i+19);
		}
	}
	fclose(A);
	return 0;	
}

/* Функция проверки соответствия способностей */
int checkAbilitiesMatch(char *Class, char *abilityName){
	
	/* Переменные */
	FILE *A; // "abilities.txt"
	FILE *H; // "heroes.txt"
	char s[31] = {0};
	char s2[31] = {0};
	
	H = fopen("data\\heroes.txt","r");
	while(!feof(H)){
		fscanf(H, "%s", s);
		if(!(strcmp(s, "Class:"))){
			fscanf(H, "%s", s);
			strcpy(Class, s);
		}
		if(!(strcmp(s, "Ability"))){
			fscanf(H, "%*s");
			fscanf(H, " %[^\n]", s);
			strcpy(abilityName, s);
			A = fopen("data\\abilities.txt","r");
			s2[0] = '\0';
			while(!feof(A)){
				fscanf(A, "%s", s2);
				if(!(strcmp(s2, "Name:"))){
					fscanf(A, " %[^\n]", s2);
					if(!(strcmp(s, s2))) break;
					continue;
				}
				if(feof(A)) return 1;
			}
			fclose(A);
		}
	}
	fclose(H);
	return 0;
}

/* Функция вывода ошибок */
void errors(int error, char *Field, char *Class, char *abilityName){		
		switch(error){			
			case 0:
				break;
			case 1:
				cout << "File \"heroes.txt\" is missing or corrupted.\n";
				break;
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
				cout << "Field \"%s\" in the class \"%s\" is incorrect or missing.\n" << Field << Class;
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
			case 15:				
				cout << "Value of \"%s\" in the class \"%s\" is incorrect.\n" << Field << Class;
				break;
			case 16:
				cout << "One or several field \"Ability\" in the class \"%s\" is missing or incorrect.\n" << Class;
				break;
			case 17:
				cout << "Wrong number of ability in the class \"%s\".\n" << Class;
				break;
			case 18:
				cout << "File \"abilities.txt\" is missing or corrupted.\n";
				break;
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
			case 28:
			case 29:
			case 30:
				cout << "Field \"%s\" in the ability \"%s\" is incorrect or missing.\n" << Field << abilityName;
				break;
			case 31:
			case 32:
			case 33:
			case 34:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
			case 40:
				cout << "Value of \"%s\" in the ability \"%s\" is incorrect.\n" << Field << abilityName;
				break;
			case 41:
				cout << "Too long name of class \"%s\".\n" << Class;
				break;
			case 42:
				cout << "Too long name of ability \"%s\" in the class \"%s\".\n" << abilityName << Class;
				break;				
		}		
	}

void TestFiles(){
	int error1, error2, error3;
	char Field[31], Class[31], abilityName[31];
	if(error1 = scanheroes(Field, Class, abilityName)){
		cout << "Error in the file \"heroes.txt\". ";
		errors(error1, Field, Class, abilityName);
	}
	if(error2 = scanabilities(Field, abilityName)){
		cout << "Error in the file \"abilities.txt\". ";
		errors(error2, Field, Class, abilityName);
	}
	if(!(error1+error2)){
		if(error3 = checkAbilitiesMatch(Class, abilityName)){
			cout << "Error: ability \"%s\" in the class \"%s\" is not found.\n" << abilityName << Class;
		}
	}
	if(error1+error2+error3){
		cout << "Press any key to exit...";
		getch();
		exit(0);
	}
}
