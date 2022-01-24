#include "newgame.h"
#include "drawings.h"
#include "mainmenu.h"
#include "navigation.h"
#include "parameters.h"
#include "globals.h"
#include "structures.h"
#include "choosehero.h"
#include <ctime>
#include <cstring>
#include <cstdlib>

/* New Game */
int NewGame(){
	unsigned int x, y, menuX, menuY, HeroID = 0, i;
	string NewGame[]{{"Choose a Hero Class"},{"Use Random Hero"},{"Back"}};
	unsigned int strings = sizeof(NewGame)/sizeof(string);
	unsigned int width = 0;
	for(i=0; i<strings; i++){
		if(NewGame[i].length() > width) width = NewGame[i].length()+6;
	}
	unsigned int height = strings*2-1;
	menuX = x = WIDTH/2-width/2;
	menuY = y = HEIGHT/2-height/2;
	DrawMenuBox(menuX, menuY, width, height);
	cursor(x+=4, ++y);
	ShowMenuPoints(x, y, NewGame, strings, 1);
	SelectString(x, y, NewGame, i=0, 1);
	if((Navigation(x, y, NewGame, i, strings, 1)) == Back){
		HideMenuBox(menuX, menuY, width, height);
		return Back;
	}
	switch(i){		
		case 0:	
			HideMenuBox(menuX, menuY, width, height);
			DrawHelm();
			while(true){
				switch(ChooseHero(ClassesQuantity, HeroID)){
					case Back: return Repeat;
					case Play: return Play;
					case Repeat: continue;
				}
			}			
		case 1:
			srand(time(NULL));
			hero = Heroes[rand() % ClassesQuantity];
			hero.name = "Unknown";
			return Play;
		case -1:
		case 2:
			HideMenuBox(menuX, menuY, width, height);
			return Back;
	}	
}
