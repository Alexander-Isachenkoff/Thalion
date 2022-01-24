#include "parameters.h"
#include "globals.h"
#include <windows.h>

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
	exit(0);
} 

void SetParameters(){
	HWND hwnd = GetConsoleWindow();
	SetWindowPos(hwnd, HWND_TOP, 0,0,0,0, SWP_HIDEWINDOW);
	
	/* Убрать рамку */	
	LONG style = GetWindowLong(hwnd, GWL_STYLE);
	style &= ~(WS_BORDER|WS_CAPTION|WS_THICKFRAME);
	SetWindowLong(hwnd, GWL_STYLE, style);
	
	/* Шрифт */
	fontInfo.cbSize = sizeof(fontInfo);
	GetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
	wcscpy(fontInfo.FaceName, L"Consolas");
	switch(GetSystemMetrics(SM_CXSCREEN)){
		case 1920: fontInfo.dwFontSize.Y = 28; break;
		case 1680:
		case 1600: fontInfo.dwFontSize.Y = 24; break;
		case 1440:
		case 1400: fontInfo.dwFontSize.Y = 22; break;
		case 1366:
		case 1360: fontInfo.dwFontSize.Y = 20; break;
		case 1280:
		case 1152: fontInfo.dwFontSize.Y = 18; break;
		case 1024: fontInfo.dwFontSize.Y = 16; break;
		
	}
	if(GetSystemMetrics(SM_CYSCREEN) < 720) fontInfo.dwFontSize.Y = 16;
	if(GetSystemMetrics(SM_CXSCREEN) < 1024) fontInfo.dwFontSize.Y = 12;
	COORD maxWindow;
	SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
	maxWindow = GetLargestConsoleWindowSize(handle);
	while(WIDTH > maxWindow.X-5){
		fontInfo.dwFontSize.Y -= 2;
		SetCurrentConsoleFontEx(handle, TRUE, &fontInfo);
		maxWindow = GetLargestConsoleWindowSize(handle);
	}
	
	/* Размер окна и буфера */
	COORD bufferSize = {WIDTH, HEIGHT};
	SMALL_RECT windowSize = {0, 0, WIDTH-1, HEIGHT-1};
	SetConsoleScreenBufferSize(handle, bufferSize);
	SetConsoleWindowInfo(handle, TRUE, &windowSize);
	
	Sleep(10);
	/* Окно по центру */
	RECT CurrentWindowSize;
	GetWindowRect(hwnd, &CurrentWindowSize);
	int w = CurrentWindowSize.right - CurrentWindowSize.left;
	int h = CurrentWindowSize.bottom - CurrentWindowSize.top;
	SetWindowPos(hwnd, HWND_TOP, (GetSystemMetrics(SM_CXSCREEN)-w)/2,(GetSystemMetrics(SM_CYSCREEN)-h)/2,w,h, SWP_SHOWWINDOW);
	
	/* Скрыть курсор */
    GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);

	/* Отключить выделение мышью */
	HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE); 
	DWORD Mode = 0;
	DWORD dwNewMode;
	GetConsoleMode(hConsole, &Mode);
	dwNewMode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hConsole, dwNewMode | ENABLE_EXTENDED_FLAGS);
	
	/* Создать папку "save" */
	CreateDirectory("save", NULL);
}
