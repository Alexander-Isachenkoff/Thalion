#include <cstring>
#include <cctype>
#include "numbers.h"

/* явл€етс€ ли строка числом */
int isnumber(char *s){
	unsigned int i;
	bool point = false, minus = false;
	for(i=0; i<strlen(s); i++){
		if((isdigit(s[i])) || ((s[i] == '.')&&(i)&&(i!=strlen(s)-1)) || ((s[i] == '-')&&(!i))){
			if(s[i] == '.'){
				if(point) return 0;
				point = true;
			}
			if(s[i] == '-'){
				if(minus) return 0;
				minus = true;
			}				
		}
		else return 0;
	}
	return 1;
}

/* явл€етс€ ли строка целым числом */
int isIntNumber(char *s){
	unsigned int i;
	bool minus = false;
	for(i=0; i<strlen(s); i++){
		if((isdigit(s[i])) || ((s[i] == '-')&&(!i))){
			if(s[i] == '-'){
				if(minus) return 0;
				minus = true;
			}				
		}
		else return 0;
	}
	return 1;
}
