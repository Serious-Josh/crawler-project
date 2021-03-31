#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>

using namespace std;

enum class elements { Fire, Ice, Earth, Forest, Wind, Normal};

//got this function from tutorialspoint, very helpful
string element_to_string(elements type) {
	switch (type) {
	case elements::Fire: return "Fire";
		break;
	case elements::Ice: return "Ice";
		break;
	case elements::Earth: return "Earth";
		break;
	case elements::Forest: return "Forest";
		break;
	case elements::Wind: return "Wind";
		break;
	case elements::Normal: return "Normal";
		break;
	}
}

//this is for things like drop chances, modifier chances
//mainly where rare chances are involved
//is out of 100
double randomPercentage() {

	double temp, temp1, temp2, num;

	temp = rand() % 101;
	temp1 = (rand() % 11) / 10;
	temp2 = (rand() % 11) / 100;

	num = temp + temp1 + temp2;

	return num;
}


class equipment {

private:

	int weight, value;
	string name;
	double shopScaler;

public:

	equipment(string name, int weight, int value, double shopScaler) {
		this->name = name;
		this->weight = weight;
		this->value = value;
		this->shopScaler = shopScaler;

	};

	int getWeight() {
		return weight;
	}

	string getName() {
		return name;
	}

	int getValue() {
		return value;
	}

	void setName(string name) {
		this->name = name;
	}

	void setWeight(int weight) {
		this->weight = weight;
	}

	void setValue(int value) {
		this->value = value;
	}

	//is for inventory purposes
	virtual string outputInfo() = 0;

};

enum class weaponType { Sword, Dagger, Spear, Axe, Bow, Default};

string weapon_to_string(weaponType type) {
	switch (type) {
	case weaponType::Sword: return "Sword";
		break;
	case weaponType::Dagger: return "Dagger";
		break;
	case weaponType::Spear: return "Spear";
		break;
	case weaponType::Axe: return "Axe";
		break;
	case weaponType::Bow: return "Bow";
		break;
	case weaponType::Default: return "NULL";
		break;
	}
}

//shop scaler is to help increase chances of better scalers, and to increase damage overall
//max shop scaler is 2
int baseDmgCalculation(weaponType type, int modifier, int shopScaler) {

	int temp;
	int damage = 0;
	double scaler;


	//scalar calculation
	temp = rand() % 101;

	if (temp < (2 * shopScaler)) {
		scaler = (rand() % 20 + 1.0);
	}
	else if ((temp < (4 * shopScaler)) && (temp >= 2)) {
		scaler = (rand() % 15 + 1.0);
	}
	else if ((temp < (10 * shopScaler)) && (temp >= 4)) {
		scaler = (rand() % 8 + 1.0);
	}
	else if ((temp < 25) && (temp >= 10)) {
		scaler = (rand() % 4 + 1.0);
	}
	else if ((temp < 50) && (temp >= 25)) {
		scaler = (rand() % 3 + 1.0);
	}
	else {
		scaler = (rand() % 2 + 1.0);
	}

	temp = (rand() % 11) / 10;
	scaler += temp;


	//quick system to help mitigate huge damage numbers
	double temp1 = (shopScaler * 0.4);


	//weapon type damage/scalar application
	switch (type) {
	case weaponType::Sword: damage = ((rand() % 34 + 22) * scaler) * temp1;
		break;
	case weaponType::Dagger: damage = ((rand() % 21 + 13) * scaler) * temp1;
		break;
	case weaponType::Spear: damage = ((rand() % 31 + 18) * scaler) * temp1;
		break;
	case weaponType::Axe: damage = ((rand() % 43 + 31) * scaler) * temp1;
		break;
	case weaponType::Bow: damage = ((rand() % 27 + 19) * scaler) * temp1;
		break;
	}

	switch (modifier) {
	case 0: break;
	case 1: damage = damage * 1.05;
		break;
	case 2: damage = damage * 1.125;
		break;
	case 3: damage = damage * 1.25;
		break;
	case 4: damage = damage * 1.35;
		break;
	case 5: damage = damage * 1.5;
		break;
	}

	return damage / (3 - shopScaler);

}

//elemental damage is a stat hidden from the player and isn't shown, but is taken into consideration when actually dealing damage
//is going to be an easy calculation of a percentage of the calculated weapon damage
//this damage will adjust based on the element of the enemy
int elemDmgCalculation(int weaponDmg, elements elem) {

	if (elem != elements::Normal) {
		return weaponDmg * 0.15;
	}
	else {
		return 0;
	}
}

class weapon : public equipment {

private:
	int dmg;
	int elemDmg;
	elements elem;
	weaponType type;
	int dmgMod;

	//shopScaler was originally just for buying from shops, but I think it'll also end up being used for dungeon levels as well
	int shopScaler;
	
public:

	weapon(string name = "NULL", int weight = 0, int value = 0, int shopScaler = 1.0) : equipment(name, weight, value, shopScaler) {

		this->shopScaler = shopScaler;

		//weapon type generation
		int tempInt = (rand() % 5 + 1);
		switch (tempInt) {
		case 1: type = weaponType::Sword;
			break;
		case 2: type = weaponType::Dagger;
			break;
		case 3: type = weaponType::Spear;
			break; 
		case 4: type = weaponType::Axe;
			break;
		case 5: type = weaponType::Bow;
			break;
		}
		
		//damage modifier generation
		double temp = randomPercentage();

		if (temp <= 0.25) {
			dmgMod = 5;
		}
		else if (temp <= 0.5 && temp > 0.25) {
			dmgMod = 4;
		}
		else if (temp <= 1 && temp > 0.5) {
			dmgMod = 3;
		}
		else if (temp <= 7.5 && temp > 1) {
			dmgMod = 2;
		}
		else if (temp <= 15 && temp > 7.5) {
			dmgMod = 1;
		}
		else {
			dmgMod = 0;
		}


		//elemental generation
		double temp2 = rand() % 101;

		//think about lowering percentage
		if (temp2 <= 12.5) {
			int temp3 = rand() % 5 + 1;

			switch (temp3) {
			case 1: elem = elements::Fire;
				break;
			case 2: elem = elements::Ice;
				break;
			case 3: elem = elements::Earth;
				break;
			case 4: elem = elements::Forest;
				break;
			case 5: elem = elements::Wind;
				break;
			}
		}
		else {
			this->elem = elements::Normal;
		}


		dmg = baseDmgCalculation(type, dmgMod, shopScaler);
		elemDmg = elemDmgCalculation(dmg, elem);

		generateInformation();

	}

	void generateInformation() {

		string name;

		//name generation
		if ((dmgMod > 0) && (elem != elements::Normal)) {
			//has both damage modifer and element
			name = weapon_to_string(type) + " of " + element_to_string(elem) + " +" + to_string(dmgMod);
		}
		else if ((dmgMod > 0) && (elem == elements::Normal)) {
			//has damage modifier but no element
			name = weapon_to_string(type) + " +" + to_string(dmgMod);
		}
		else if ((dmgMod == 0) && (elem != elements::Normal)) {
			//no damage modifier but has element
			name = weapon_to_string(type) + " of " + element_to_string(elem);
		}
		else {
			//no damage modifier or element
			name = weapon_to_string(type);
		}

		setName(name);

		if ((dmgMod > 0) && (elem != elements::Normal)) {
			//has both damage modifer and element
			setValue(((dmg * 0.75) + (elemDmg * 0.85)) * (2.5*dmgMod));
		}
		else if ((dmgMod > 0) && (elem == elements::Normal)) {
			//has damage modifier but no element
			setValue(((dmg * 0.75) + (elemDmg * 0.85)) * (1.75*dmgMod));
		}
		else if ((dmgMod == 0) && (elem != elements::Normal)) {
			//no damage modifier but has element
			setValue(((dmg * 0.75) + (elemDmg * 0.85)) * 1.75);
		}
		else {
			//no damage modifier or element
			setValue((dmg * 0.75) + (elemDmg * 0.85));
		}

	}

	string outputInfo() {
		return to_string(getDamage());
	}

	int getDamage() {
		return dmg;
	}

	string getElement() {
		return element_to_string(elem);
	}

	int getElementalDamage() {
		return elemDmg;
	}

};



enum class accessType { HP, MP, Str, Mag, End, Spd };

string access_to_string(accessType type) {
	switch (type) {
	case accessType::HP: return "HP";
		break;
	case accessType::MP: return "MP";
		break;
	case accessType::Str: return "Str";
		break;
	case accessType::Mag: return "Mag";
		break;
	case accessType::End: return "End";
		break;
	case accessType::Spd: return "Spd";
		break;
	}
}

class accessories : public equipment {

private:
	accessType type;

public:
	accessories(string name = "NULL", int weight = 0, int value = 1, double shopScaler = 1.0):equipment(name, weight, value, shopScaler) {

		generateInformation();

	}

	void generateInformation() {

		int temp = randomPercentage();

		if (temp < 21) {
			type = accessType::HP;
			setName("Band of Health");
		}
		else if (temp < 41) {
			type = accessType::MP;
			setName("Band of Aether");
		}
		else if (temp < 56) {
			type = accessType::Str;
			setName("Ring of Power");
		}
		else if (temp < 71) {
			type = accessType::Mag;
			setName("Ring of Magic");
		}
		else if (temp < 86) {
			type = accessType::End;
			setName("Ring of Endurance");
		}
		else {
			type = accessType::Spd;
			setName("Ring of Quickness");
		}

	}

	accessType getType() {
		return type;
	}

	string outputInfo() {
		return access_to_string(type);
	}

};



class armor : public equipment {

private:
	int armorStat, tempArmor;

public:
	
	armor(string name = "NULL", int weight = 0, int value = 1, double shopScaler = 1.0, int armor = 0): equipment(name, weight, value, shopScaler) {

		int temp = randomPercentage();

		if (temp < (1 * shopScaler)) {
			armorStat = (rand() % 56 * shopScaler) + 34;
		}
		else if (temp < (4 * shopScaler)) {
			armorStat = (rand() % 44 * shopScaler) + 34;
		}
		else if (temp < (10 * shopScaler)) {
			armorStat = (rand() % 32 * shopScaler) + 22;
		}
		else if (temp < (25 * shopScaler)) {
			armorStat = (rand() % 23) + 12;
		}
		else {
			armorStat = (rand() % 12) + 5;
		}

		generateInformation();

	}

	void generateInformation() {

		string type, material;
		int temp;

		temp = rand() % 100 + 1;

		if (temp < 25) {
			type = "Head";
		}
		else if ((temp < 50) && (temp >= 25)) {
			type = "Breatplate";
		}
		else if ((temp >= 50) && (temp < 75)) {
			type = "Gauntlets";
		}
		else {
			type = "Boots";
		}

		temp = rand() % 100 + 1;

		if (temp < 25) {
			material = "Steel";
			setArmor(getArmor() * 1.75);
		}
		else if ((temp < 50) && (temp >= 25)) {
			material = "Cloth";
			setArmor(getArmor() * 1.2);
		}
		else if ((temp >= 50) && (temp < 75)) {
			material = "Chainmail";
			setArmor(getArmor() * 1.6);
		}
		else {
			material = "Leather";
			setArmor(getArmor() * 1.35);
		}

		setName(material + " " + type);

		tempArmor = armorStat;

	}

	int getArmor() {
		return armorStat;
	}

	string outputInfo() {
		return to_string(getArmor());
	}

	void setArmor(int armor) {
		armorStat = armor;
	}

	int getTempArmor() {
		return tempArmor;
	}

	void setTempArmor(int armor) {
		tempArmor = armor;
	}
	

};