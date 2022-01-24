#include "parameters.h"
#include "verification.h"
#include "datascanning.h"
#include "enemies.h"
#include "intro.h"
#include "mainmenu.h"
#include "game.h"
int main(){
	SetParameters(); // Запуск
	TestFiles(); // Проверка файлов
	DataScanning(); // Запись героев
	SetEnemiesStats(); // Запись врагов
	Intro(); // Вступление
	while(true){
		switch(MainMenu()){
			case Back: Quit();						
			case Repeat: continue;
			case Play: 
				StartGame();
				continue;
		}
	}	
}
