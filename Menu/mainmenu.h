#ifndef mainmenu
#define mainmenu
#include <string>
#include "globals.h"
using namespace std;
void DrawMenuBox(unsigned int, unsigned int, unsigned int, unsigned int);
void DrawInputBox(unsigned int, unsigned int, unsigned int, unsigned int);
void HideMenuBox(unsigned int, unsigned int, unsigned int, unsigned int);
void ShowMenuPoints(unsigned int, unsigned int, string *, unsigned int, unsigned int);
int MainMenu();
#endif
