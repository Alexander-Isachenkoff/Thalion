#ifndef abilitiesnav
#define abilitiesnav
#include <string>
#include "structures.h"
void DrawAbilityBox(unsigned int, string, unsigned int);
void DrawDescriptionBox(unsigned int, unsigned int);
void HideDescriptionBox(unsigned int);
void ShowAbilityDescription(unsigned int);
void SelectAbility(unsigned int);
void SelectAbilityRight(unsigned int &);
void SelectAbilityLeft(unsigned int &);
int AbilityNavigation(unsigned int &);
#endif
