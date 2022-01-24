#ifndef navigation
#define navigation
#include <string>
#include "globals.h"
using namespace std;
int Navigation(unsigned int, unsigned int, string *, unsigned int &, unsigned int, unsigned int);
void SelectString(unsigned int, unsigned int &, string *, unsigned int, unsigned int);
void SelectUp(unsigned int &, unsigned int &, string *, unsigned int &, unsigned int);
void SelectDown(unsigned int &, unsigned int &, string *, unsigned int &, unsigned int);
#endif
