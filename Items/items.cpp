#include "items.h"
#include "globals.h"
#include "structures.h"
#include "datascanning.h"
#include <cstdlib>
#include <ctime>

/* Эффекты предметов */
	/* Расходники */
void PlusHP(){
	hero.hp += 5;
	if(hero.hp > hero.maxhp) hero.hp = hero.maxhp;
}
void PlusKey(){
	hero.keys++;
}
	/* Слабые */
void LowHpUp(){
	hero.hp += 5;
	hero.maxhp += 5;
}
void LowAccUp(){
	hero.acc += 0.1;
}
void LowDmgUp(){
	if(hero.minDmg < hero.maxDmg) hero.minDmg++;
	else
	hero.maxDmg++;
}
void LowCritUp(){
	hero.crit += 0.05;
	if(hero.crit > 0.5) hero.crit = 0.5;
}
void LowDodgeUp(){
	hero.dodge += 0.05;
	if(hero.dodge > 0.5) hero.dodge = 0.5;
}
void LowDefenceUp(){	
	hero.def += 0.05;
	if(hero.def > 0.5) hero.def = 0.5;
}
void LowBleedUp(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].bleedChance > 0){		
			hero.ability[i].bleedDmg++;
			hero.ability[i].bleedChance += 0.1;
			AbilityDescription(hero, i);
		}
	}	
}
void LowPoisonUp(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].poisonChance > 0){		
			hero.ability[i].poisonDmg++;
			hero.ability[i].poisonChance += 0.1;
			AbilityDescription(hero, i);
		}
	}
}
void LowStunUp(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].stun > 0) hero.ability[i].stun += 0.1;
		AbilityDescription(hero, i);
	}
}

	/* Сильные */
void HighHpUp(){
	hero.hp += 10;
	hero.maxhp += 10;
}
void HighAccUp(){
	hero.acc += 0.15;
}
void HighDmgUp(){
	hero.minDmg++;
	hero.maxDmg++;
}
void HighCritUp(){
	hero.crit += 0.1;
	if(hero.crit > 0.5) hero.crit = 0.5;
}
void HighDodgeUp(){
	hero.dodge += 0.1;
	if(hero.dodge > 0.5) hero.dodge = 0.5;
}
void HighDefenceUp(){
	hero.def += 0.1;
	if(hero.def > 0.5) hero.def = 0.5;
}
void HighBleedUp(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].bleedChance > 0){		
			hero.ability[i].bleedDmg++;
			hero.ability[i].bleedChance += 0.15;
			AbilityDescription(hero, i);
		}
	}
}
void HighPoisonUp(){
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].poisonChance > 0){		
			hero.ability[i].poisonDmg++;
			hero.ability[i].poisonChance += 0.15;
			AbilityDescription(hero, i);
		}
	}
}
void HighStunUp(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].stun > 0) hero.ability[i].stun += 0.15;
		AbilityDescription(hero, i);
	}
}

/* Дебафы */
	/* Слабые */
void LowHpDown(){
	hero.maxhp -= 5;
	if(hero.maxhp <= 0) hero.maxhp = 10;
	if(hero.hp > hero.maxhp) hero.hp = hero.maxhp;
}
void LowAccDown(){
	if(hero.acc > 0.1) hero.acc -= 0.1;
}
void LowDmgDown(){
	if(hero.minDmg > 1) hero.minDmg--;
}
void LowCritDown(){
	if(hero.crit > 0) hero.crit -= 0.05;
	if(hero.crit < 0) hero.crit = 0;
}
void LowDodgeDown(){
	if(hero.dodge > 0) hero.dodge -= 0.05;
	if(hero.dodge < 0) hero.dodge = 0;
}
void LowDefenceDown(){
	if(hero.def > 0) hero.def -= 0.05;
	if(hero.def < 0) hero.def = 0;
}
void LowBleedDown(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].bleedChance > 0.1){		
			if(hero.ability[i].bleedDmg > 1) hero.ability[i].bleedDmg--;
			hero.ability[i].bleedChance -= 0.1;
		}
	}
}
void LowPoisonDown(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].poisonChance > 0.1){		
			if(hero.ability[i].poisonDmg > 1) hero.ability[i].poisonDmg--;
			hero.ability[i].poisonChance -= 0.1;
		}
	}
}
void LowStunDown(){	
	for(unsigned int i=0; i<4; i++){
		if(hero.ability[i].stun > 0.1) hero.ability[i].stun -= 0.1;
	}
}
void None(){
}

/* Эффекты брони */
	/* Кожаная */
void LeatherHelm(){
	hero.def += 0.05;
	if(hero.def > 0.5) hero.def = 0.5;
	LowDodgeUp();
}
void LeatherArmor(){
	hero.def += 0.1;
	if(hero.def > 0.5) hero.def = 0.5;
	LowDodgeUp();
}
void LeatherGloves(){
	hero.def += 0.05;
	if(hero.def > 0.5) hero.def = 0.5;
	LowDodgeUp();
}
void LeatherPants(){
	hero.def += 0.07;
	if(hero.def > 0.5) hero.def = 0.5;
	LowDodgeUp();
}
void LeatherBoots(){
	hero.def += 0.05;
	if(hero.def > 0.5) hero.def = 0.5;
	LowDodgeUp();
}
void GoodCloak(){
	LowDodgeUp();
	hero.acc += 0.1;
}
void LuxuriousCloak(){
	HighDodgeUp();
	hero.acc += 0.1;
}
	
	/* Тяжёлая */
void HeavyHelm(){
	hero.def += 0.1;
	if(hero.def > 0.5) hero.def = 0.5;
	hero.dodge -= 0.05;
	if(hero.dodge < 0) hero.dodge = 0;
}
void HeavyArmor(){
	hero.def += 0.2;
	if(hero.def > 0.5) hero.def = 0.5;
	hero.dodge -= 0.1;
	if(hero.dodge < 0) hero.dodge = 0;
}
void HeavyGloves(){
	hero.def += 0.1;
	if(hero.def > 0.5) hero.def = 0.5;
	hero.dodge -= 0.1;
	if(hero.dodge < 0) hero.dodge = 0;
}
void HeavyPants(){
	hero.def += 0.15;
	if(hero.def > 0.5) hero.def = 0.5;
	hero.dodge -= 0.7;
	if(hero.dodge < 0) hero.dodge = 0;
}
void HeavyBoots(){
	hero.def += 0.1;
	if(hero.def > 0.5) hero.def = 0.5;
	hero.dodge -= 0.05;
	if(hero.dodge < 0) hero.dodge = 0;
}

/* Оружие */
void BalancedSword(){
	LowDmgUp();
	LowAccUp();
}
void LightDagger(){
	LowDmgUp();
	LowDodgeUp();	
}

/* Определить кольцо */
void SetRing(unsigned int ItemID){
	unsigned int P;
	Items[ItemID].name = "Mystery Ring";
	Items[ItemID].description = "++? -?";
	Items[ItemID].price = 15;
	P = rand() % 9;
	switch(P){
		case 0: Items[ItemID].Buf = HighAccUp; break;
		case 1: Items[ItemID].Buf = HighCritUp; break;
		case 2: Items[ItemID].Buf = HighDmgUp; break;
		case 3: Items[ItemID].Buf = HighDodgeUp; break;
		case 4: Items[ItemID].Buf = HighDefenceUp; break;
		case 5: Items[ItemID].Buf = HighBleedUp; break;
		case 6: Items[ItemID].Buf = HighPoisonUp; break;
		case 7: Items[ItemID].Buf = HighStunUp; break;
		case 8: Items[ItemID].Buf = HighHpUp; break;
	}
	P = rand() % 9;
	switch(P){
		case 0: Items[ItemID].Debuf = LowAccDown; break;
		case 1: Items[ItemID].Debuf = LowCritDown; break;
		case 2: Items[ItemID].Debuf = LowDmgDown; break;
		case 3: Items[ItemID].Debuf = LowDodgeDown; break;
		case 4: Items[ItemID].Debuf = LowDefenceDown; break;
		case 5: Items[ItemID].Debuf = LowBleedDown; break;
		case 6: Items[ItemID].Debuf = LowPoisonDown; break;
		case 7: Items[ItemID].Debuf = LowStunDown; break;
		case 8: Items[ItemID].Debuf = LowHpDown; break;
	}
};

/* Установка предметов */
void SetItems(){
	srand(time(NULL));
	unsigned int ItemID;	
	
	/* Слабые предметы */
	ItemID = Health_Stone;
	Items[ItemID].name = "Health Stone";
	Items[ItemID].description = "+Max HP";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighHpUp;
	Items[ItemID].Debuf = None;	

	ItemID = Accuracy_Stone;
	Items[ItemID].name = "Accuracy Stone";
	Items[ItemID].description = "+Accuracy";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowAccUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Bleed_Stone;
	Items[ItemID].name = "Bleed Stone";
	Items[ItemID].description = "+Bleed";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowBleedUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Poison_Stone;
	Items[ItemID].name = "Poison Stone";
	Items[ItemID].description = "+Poison";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowPoisonUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Critical_Stone;
	Items[ItemID].name = "Critical Stone";
	Items[ItemID].description = "+Crit";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowCritUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Dodge_Stone;
	Items[ItemID].name = "Dodge Stone";
	Items[ItemID].description = "+Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowDodgeUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Protection_Stone;
	Items[ItemID].name = "Protection Stone";
	Items[ItemID].description = "+Defence";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowDefenceUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Damage_Stone;
	Items[ItemID].name = "Damage Stone";
	Items[ItemID].description = "+Damage";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowDmgUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Stun_Stone;
	Items[ItemID].name = "Stun Stone";
	Items[ItemID].description = "+Stun";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowStunUp;
	Items[ItemID].Debuf = None;
	
	/* Сильные предметы */
	ItemID = Health_Amulet;
	Items[ItemID].name = "Health Amulet";
	Items[ItemID].description = "++Max HP";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighHpUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Accuracy_Amulet;
	Items[ItemID].name = "Accuracy Amulet";
	Items[ItemID].description = "++Accuracy";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighAccUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Bleed_Amulet;
	Items[ItemID].name = "Bleed Amulet";
	Items[ItemID].description = "++Bleed";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighBleedUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Poison_Amulet;
	Items[ItemID].name = "Poison Amulet";
	Items[ItemID].description = "++Poison";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighPoisonUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Critical_Amulet;
	Items[ItemID].name = "Critical Amulet";
	Items[ItemID].description = "++Crit";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighCritUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Dodge_Amulet;
	Items[ItemID].name = "Dodge Amulet";
	Items[ItemID].description = "+Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighDodgeUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Protection_Amulet;
	Items[ItemID].name = "Protection Amulet";
	Items[ItemID].description = "++Defence";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighDefenceUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Damage_Amulet;
	Items[ItemID].name = "Damage Amulet";
	Items[ItemID].description = "++Damage";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighDmgUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Stun_Amulet;
	Items[ItemID].name = "Stun Amulet";
	Items[ItemID].description = "++Stun";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = HighStunUp;
	Items[ItemID].Debuf = None;
	
	/* Загадочные кольца */
	SetRing(Mystery_Ring1);
	SetRing(Mystery_Ring2);
	SetRing(Mystery_Ring3);
	SetRing(Mystery_Ring4);
	SetRing(Mystery_Ring5);
	
	/* Слабая броня */
	ItemID = Leather_Helm;
	Items[ItemID].name = "Leather Helm";
	Items[ItemID].description = "+Defence +Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LeatherHelm;
	Items[ItemID].Debuf = None;
	
	ItemID = Leather_Armor;
	Items[ItemID].name = "Leather Armor";
	Items[ItemID].description = "++Defence +Dodge";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = LeatherArmor;
	Items[ItemID].Debuf = None;
	
	ItemID = Leather_Gloves;
	Items[ItemID].name = "Leather Gloves";
	Items[ItemID].description = "+Defence +Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LeatherGloves;
	Items[ItemID].Debuf = None;
	
	ItemID = Leather_Pants;
	Items[ItemID].name = "Leather Pants";
	Items[ItemID].description = "+Defence +Dodge";
	Items[ItemID].price = 30;
	Items[ItemID].Buf = LeatherPants;
	Items[ItemID].Debuf = None;
	
	ItemID = Leather_Boots;
	Items[ItemID].name = "Leather Boots";
	Items[ItemID].description = "+Defence +Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LeatherBoots;
	Items[ItemID].Debuf = None;
	
	/* Сильная броня */
	ItemID = Heavy_Helm;
	Items[ItemID].name = "Heavy Helm";
	Items[ItemID].description = "++Defence -Dodge";
	Items[ItemID].price = 30;
	Items[ItemID].Buf = HeavyHelm;
	Items[ItemID].Debuf = None;
	
	ItemID = Heavy_Armor;
	Items[ItemID].name = "Heavy Armor";
	Items[ItemID].description = "+++Defence -Dodge";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = HeavyArmor;
	Items[ItemID].Debuf = None;
	
	ItemID = Heavy_Gloves;
	Items[ItemID].name = "Heavy Gloves";
	Items[ItemID].description = "++Defence -Dodge";
	Items[ItemID].price = 30;
	Items[ItemID].Buf = HeavyGloves;
	Items[ItemID].Debuf = None;
	
	ItemID = Heavy_Pants;
	Items[ItemID].name = "Heavy Pants";
	Items[ItemID].description = "++Defence -Dodge";
	Items[ItemID].price = 35;
	Items[ItemID].Buf = HeavyPants;
	Items[ItemID].Debuf = None;
	
	ItemID = Heavy_Boots;
	Items[ItemID].name = "Heavy Boots";
	Items[ItemID].description = "++Defence -Dodge";
	Items[ItemID].price = 30;
	Items[ItemID].Buf = HeavyBoots;
	Items[ItemID].Debuf = None;
	
	/* Плащи */
	ItemID = Old_Cloak;
	Items[ItemID].name = "Old Cloak";
	Items[ItemID].description = "+Dodge";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowDodgeUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Good_Cloak;
	Items[ItemID].name = "Good Cloak";
	Items[ItemID].description = "+Dodge +Accuracy";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = GoodCloak;
	Items[ItemID].Debuf = None;
	
	ItemID = Luxurious_Cloak;
	Items[ItemID].name = "Luxurious_Cloak";
	Items[ItemID].description = "++Dodge +Accuracy";
	Items[ItemID].price = 50;
	Items[ItemID].Buf = LuxuriousCloak;
	Items[ItemID].Debuf = None;

	/* Оружие */
	ItemID = Steel_Sword;
	Items[ItemID].name = "Steel Sword";
	Items[ItemID].description = "+Damage";
	Items[ItemID].price = 25;
	Items[ItemID].Buf = LowDmgUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Battle_Axe;
	Items[ItemID].name = "Battle Axe";
	Items[ItemID].description = "++Damage";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = HighDmgUp;
	Items[ItemID].Debuf = None;
	
	ItemID = Balanced_Sword;
	Items[ItemID].name = "Balanced Sword";
	Items[ItemID].description = "+Damage +Acc";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = BalancedSword;
	Items[ItemID].Debuf = None;
	
	ItemID = Light_Dagger;
	Items[ItemID].name = "Light Dagger";
	Items[ItemID].description = "+Damage +Dodge";
	Items[ItemID].price = 40;
	Items[ItemID].Buf = LightDagger;
	Items[ItemID].Debuf = None;
	
	/* Расходники */
	ItemID = Health;
	Items[ItemID].name = "Health Potion";
	Items[ItemID].description = "+HP";
	Items[ItemID].price = 10;
	Items[ItemID].Buf = PlusHP;
	Items[ItemID].Debuf = None;
	
	ItemID = Key;
	Items[ItemID].name = "Key";
	Items[ItemID].description = "+Key";
	Items[ItemID].price = 10;
	Items[ItemID].Buf = PlusKey;
	Items[ItemID].Debuf = None;
}
