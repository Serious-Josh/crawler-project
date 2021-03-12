#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "Equipment.h"
#include "Room.h"

using namespace std;

class player {
private:
	string name;
	int level;
	int hp, tempHP, mp, maxHP;
	int str, mag, spd, end; //stats
	int curExp, needExp, totExp;
	int guardArmor;
	bool guard;
	vector<weapon*> weapons;
	vector<armor*> armors;
	weapon* playerWeapon; //equiped weapon
	armor* playerArmor; //equiped armor
	room* currRoom;
	

public:

	player(string name = "NULL") {

		guard = false;

		srand(time(NULL));

		//random stat generation
		str = rand() % 12 + 1;
		mag = rand() % 12 + 1;
		spd = rand() % 12 + 1;
		end = rand() % 12 + 1;

		//standard initialization
		this->name = name;
		level = 1;
		hp = sqrt((pow(end, 5)/358)) + 200;
		mp = sqrt((pow(mag, 3)/2.1));


	}

	//returns the room number the player is in
	room* getLocation() {
		return currRoom;
	}


	void setLocation(room* location) {
		this->currRoom = location;
	}

	void moveLocation(vector<room*> roomList) {

		cout << "Which room do you want to move to:" << endl;
		string input;

		if (getLocation()->getEast() != nullptr) {
			cout << "East" << endl;
		}

		if (getLocation()->getWest() != nullptr) {
			cout << "West" << endl;
		}

		if (getLocation()->getNorth() != nullptr) {
			cout << "North" << endl;
		}

		if (getLocation()->getSouth() != nullptr) {
			cout << "South" << endl;
		}

		cout << endl;

		cin >> input;

			if ((input == "East") || (input == "east")) {
				setLocation(currRoom->getEast());
			}
			else if ((input == "West") || (input == "west")) {
				setLocation(currRoom->getWest());
			}
			else if ((input == "North") || (input == "north")) {
				setLocation(currRoom->getNorth());
			}
			else if ((input == "South") || (input == "south")) {
				setLocation(currRoom->getNorth());
			}
			else {
				cout << "Invalid input. Please try again." << endl << endl;
				system("PAUSE");
				system("CLS");
			}

	}

	void setName(string name) {
		this->name = name;
	}

	int getMaxHP() {
		return maxHP;
	}

	void setMaxHP(int hp) {
		maxHP = hp;
	}


	void gainEXP(int exp) {
		totExp += exp;

		if (exp > needExp) {
			curExp = (exp - needExp);
			level += 1;

			str += rand() % 2 + 1;
			mag += rand() % 2 + 1;
			spd += rand() % 2 + 1;
			end += rand() % 2 + 1;
			maxHP += rand() % 100 + 14;
		}
		else {
			curExp += exp;
		}
	}

	void outputWeapons() {

		//showing currently equipped armor to compare against
		cout << "Currently Equipped: " << playerWeapon->getName() << " - " << playerWeapon->getDamage() << " Attack" << endl << endl << "Inventory: " << endl;

		if (weapons.size() != 0) {
			for (int i = 1; (i - 1) < weapons.size(); i++) {
				cout << i << ". " << weapons[(i - 1)]->getName() << " - " << weapons[(i - 1)]->outputInfo() << " Attack" << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void swapWeapons() {

		unsigned int newWeap;

		if (weapons.empty()) {
			cout << "You have no weapons to swap to." << endl;
		}
		else {

			cout << endl << "What weapon would you like to equip?" << endl;
			cin >> newWeap;


			weapons.push_back(playerWeapon);
			equipWeapon(weapons[(newWeap - 1)]);
			weapons.erase(weapons.begin() + (newWeap - 1));
		}
	}

	void swapArmor() {

		unsigned int newArmor;

		if (armors.empty()) {
			cout << "You have no armor to swap to." << endl << endl;
			system("PAUSE");
		}
		else {

			cout << endl << "What armor would you like to equip?" << endl;
			cin >> newArmor;


			armors.push_back(playerArmor);
			equipArmor(armors[(newArmor - 1)]);
			armors.erase(armors.begin() + (newArmor - 1));
		}
	}


	void outputArmor() {

		//showing currently equipped armor to compare against
		cout << "Currently Equipped: " << playerArmor->getName() << " - " << playerArmor->getArmor() << " Armor" << endl << endl << "Inventory: " << endl;


		if (armors.size() != 0) {
			for (int i = 1; (i - 1) < armors.size(); i++) {
				cout << i << ". " << armors[(i - 1)]->getName() << " - " << armors[(i - 1)]->outputInfo() << " Armor" << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void addWeapon(weapon* weapon) {
		weapons.push_back(weapon);
	}

	void addArmor(armor* armor) {
		armors.push_back(armor);
	}

	string getName() {
		return name;
	}

	int getLevel() {
		return level;
	}

	int getHP() {
		return hp;
	}

	int getMP() {
		return mp;
	}

	int getStr() {
		return str;
	}

	int getMag() {
		return mag;
	}

	int getSpd() {
		return spd;
	}

	int getEnd() {
		return end;
	}

	void setHP(int num) {
		hp = num;
	}

	int getTempHP() {
		return tempHP;
	}

	void setTempHP(int hp) {
		tempHP = hp;
	}

	void playerDamage(int damage) {

		if (damage < 0) {
			setGuardArmor(getGuardArmor() * 0.8);
		}
		else {
			if (getHP() - damage < 0) {
				setHP(0);
			}
			else {
				setTempHP(getHP());
				setHP(getHP() - damage);
			}
		}
	}

	int getEquipArmor() {
		return playerArmor->getArmor();
	}

	int playerAttack(int armor) {

		int damage = (playerWeapon->getDamage() + playerWeapon->getElementalDamage()) - armor;

		if (damage < 0) {
			damage = 0;
		}
		else {
			damage = damage;
		}

		return damage;
	}

	int getGuardArmor() {
		return guardArmor;
	}

	void setGuardArmor(int armor) {
		guardArmor = armor;
	}

	bool getGuard() {
		return guard;
	}

	void setGuard(bool flag) {
		guard = flag;
	}


	void guardFun(int i) {

		if (i == 1) {
			setGuardArmor(playerArmor->getArmor());
			setGuard(false);
		}
		else {
			setGuardArmor(guardArmor * 1.5);
			setGuard(true);
		}
	}

	void equipWeapon(weapon* weapon) {
		playerWeapon = weapon;
	}

	void equipArmor(armor* armor) {
		playerArmor = armor;
	}

};

ostream& operator<<(ostream& os, player* player) {
	os << player->getName() << endl << "Level: " << player->getLevel() << endl << "HP: " << player->getHP() << endl << "MP: " << player->getMP() << endl << endl << "Strength: " << player->getStr() << endl << "Magic: " << player->getMag() << endl;
	os << "Speed: " << player->getSpd() << endl << "Endurance: " << player->getEnd() << endl;

	return os;
}