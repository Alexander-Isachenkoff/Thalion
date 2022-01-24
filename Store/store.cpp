#include "store.h"
#include "globals.h"
#include "structures.h"
#include "hud.h"
#include "parameters.h"
#include "mainmenu.h"
#include <conio.h>
#include <string>
#include <iostream>
#include <windows.h>
#include <MMSystem.h>

unsigned const int STORE_W = 23;
unsigned const int STORE_H = 19;

/* Кнопка назад */
void PrintQuit(){
	cursor(WIDTH-3-(STORE_W+8)/2, STORE_H-1);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 8));
	fputs("  Quit  ", stdout);
}
void SelectQuit(){
	mciSendString("stop sounds\\select2.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select2.mp3", NULL, 0, NULL);
	cursor(WIDTH-3-(STORE_W+8)/2, STORE_H-1);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs("> ", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	fputs("Quit", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs(" <", stdout);
}

void SelectGood(unsigned int x, unsigned int &y, Item *Goods, unsigned int i){
	mciSendString("stop sounds\\select2.mp3", NULL, 0, NULL);
	mciSendString("play sounds\\select2.mp3", NULL, 0, NULL);	
	cursor(x-2,y+=3*i);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 12));
	fputs("> ", stdout);
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 15));
	fputs(Goods[i].name.c_str(), stdout);	
}

void SelectGoodUp(unsigned int &x, unsigned int &y, Item *Goods, unsigned int &i){
	cursor(x-2, y);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	y-=3*i;
	cout <<"  "<< Goods[i--].name;	
	SelectGood(x, y, Goods, i);
}

void SelectGoodDown(unsigned int &x, unsigned int &y, Item *Goods, unsigned int &i){
	cursor(x-2, y);	
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
	y-=3*i;
	cout <<"  "<< Goods[i++].name;	
	SelectGood(x, y, Goods, i);
}

/* Вывести товары */
void ShowGoods(unsigned int X, unsigned int Y, Item *Goods, unsigned int GoodsQuantity){
	unsigned int i, x, y;
	cursor(x = X, y = Y);
	for(i=0; i<GoodsQuantity; i++){
		color(7);
		cout << Goods[i].name;
		color(14);
		cursor(WIDTH-5, y);
		cout << Goods[i].price;
		color(8);
		cursor(x, ++y);
		cout << "[" << Goods[i].description << "]";
		cursor(x, y+=2);		
	}
	PrintQuit();
	SelectGood(X, Y, Goods, i=0);
}

/* Навигация в магазине */
int ShopNavigation(unsigned int x, unsigned int y, Item *Goods, unsigned int &i, unsigned int GoodsQuantity){
	char select = 0;
	while((select != ' ') && (select != 13) && (select != 27)){
		select = getch();		
		switch(select){
			case 72:
				if(i == GoodsQuantity){
					PrintQuit();
					SelectGood(x, y, Goods, --i);
				}
				else
				if(i>0) SelectGoodUp(x, y, Goods, i);
				break;
			case 80:
				if(i<GoodsQuantity-1) SelectGoodDown(x, y, Goods, i);
				else
				if(i==GoodsQuantity-1){
					cursor(x-2, y);	
					SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | 7));
					y-=3*i;
					cout <<"  "<< Goods[GoodsQuantity-1].name;
					i = GoodsQuantity;
					SelectQuit();
				}
				break;
			case 27: return Back;
		}
	}
	if(i == GoodsQuantity) return Back;
	else return Next;
}

void Shop(Item *Goods, unsigned int &GoodsQuantity){
	unsigned int x, y, i, HUDx, HUDy;
	char select = 0;
	
	/* Вывести меню товаров */
	DrawHudBox(HUDx = WIDTH-STORE_W-3, HUDy = 0, STORE_W, STORE_H, "STORE");
	if(GoodsQuantity) ShowGoods(x = HUDx+3, y = HUDy+3, Goods, GoodsQuantity);
		
	while(GoodsQuantity){		
		if(ShopNavigation(x, y, Goods, i=0, GoodsQuantity) == Back){
			HideMenuBox(WIDTH-STORE_W-3, 0, STORE_W-2, STORE_H-1);
			return;
		}
		if(hero.gold >= Goods[i].price){
			mciSendString("stop sounds\\coins.mp3", NULL, 0, NULL);
			mciSendString("play sounds\\coins.mp3", NULL, 0, NULL);
			hero.gold -= Goods[i].price;
			Goods[i].Buf();
			Goods[i].Debuf();
			PrintAllStats();
			GoodsQuantity--;
			for(; i<GoodsQuantity; i++) Goods[i] = Goods[i+1];
			
			/* Обновить магазин */
			DrawHudBox(HUDx = WIDTH-STORE_W-3, HUDy = 0, STORE_W, STORE_H, "STORE");
			if(GoodsQuantity) ShowGoods(x = HUDx+3, y = HUDy+3, Goods, GoodsQuantity);
		}
	}
	SelectQuit();
	while((select != ' ') && (select != 13) && (select != 27)) select = getch();
	HideMenuBox(WIDTH-STORE_W-3, 0, STORE_W-2, STORE_H-1);
}
