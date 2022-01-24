#include "parameters.h"
#include "globals.h"
#include <iostream>
#include <cmath>

/* Переместить курсор */
void cursor(unsigned int x, unsigned int y){
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}

/* Установить цвет */
void color(unsigned int color){
	SetConsoleTextAttribute(handle, (WORD) ((0 << 4) | color));
}

/* Выход */
void Quit(){
	delete [] Heroes;
	ClipCursor(NULL);
	SetCursorPos(GetSystemMetrics(SM_CXSCREEN)/2, GetSystemMetrics(SM_CYSCREEN)/2);
	exit(0);
} 

void SetParameters(){
	
	HWND game = GetForegroundWindow(); // Получить окно
	SetWindowPos(game, HWND_TOP, 0,0,0,0, SWP_HIDEWINDOW); // Скрыть окно
	
	/* Расчёт размера шрифта */
	int font, fontsize = 6, min = 1000, epsilon;
	COORD maxWindow;
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
	wcscpy(fontInfo.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
	for(font = 6; font <= 32; font++){
		fontInfo.dwFontSize.Y = font;
		SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
		maxWindow = GetLargestConsoleWindowSize(handle);
		fontInfo.dwFontSize.Y = round((double)maxWindow.X/WIDTH*font);
		SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
		maxWindow = GetLargestConsoleWindowSize(handle);
		epsilon = maxWindow.X - WIDTH;
		if((epsilon < min)&&(epsilon >= 0)){
			min = epsilon;
			fontsize = font;
		}
	}
	fontInfo.dwFontSize.Y = fontsize;
	SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
	maxWindow = GetLargestConsoleWindowSize(handle);
	fontInfo.dwFontSize.Y = round((double)maxWindow.X/WIDTH*fontsize);
	SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);	
	
	SetWindowPos(game, HWND_TOP, 0,0,0,0, SWP_SHOWWINDOW); // Открыть окно
	Sleep(50);
	
	/* Развернуть на весь экран */	
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),KEYEVENTF_KEYUP,0);
    
    /* Установить размер буфера */
    CONSOLE_SCREEN_BUFFER_INFO bufferinfo;
    Sleep(50);
    maxWindow = GetLargestConsoleWindowSize(handle);  	    	
	GetConsoleScreenBufferInfo(handle, &bufferinfo);
	SetConsoleScreenBufferSize(handle, maxWindow);  	
	GetConsoleScreenBufferInfo(handle, &bufferinfo);
	WIDTH = bufferinfo.dwSize.X;
    HEIGHT = bufferinfo.dwSize.Y;
    
    /* Убрать полосы прокрутки повторным сворачиванием/разворачиванием */
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),0,0);
    keybd_event(VK_RETURN,MapVirtualKeyA(VK_RETURN,0),KEYEVENTF_KEYUP,0);
    keybd_event(VK_MENU,MapVirtualKeyA(VK_MENU,0),KEYEVENTF_KEYUP,0);
    	
	/* Отключить выделение мышью */
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE); 
	DWORD Mode = 0;
	DWORD dwNewMode;
	GetConsoleMode(hConsole, &Mode);
	dwNewMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hConsole, dwNewMode | ENABLE_EXTENDED_FLAGS);
    
	/* Скрыть курсор */
    GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	
	/* Убрать мышь */
	RECT rect1;
	SetRect(&rect1, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN), GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	ClipCursor(&rect1);
	
	/* Создать папку "save" */
	CreateDirectory("save", NULL);
}
