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
	bool guard;
	vector<weapon*> weapons;
	vector<armor*> armors;
	vector<accessories*> accessory;
	weapon* playerWeapon; //equiped weapon
	armor* playerArmor; //equiped armor
	accessories* playerAccess;
	room* currRoom;

	//for attack debuffs
	int normDamage, tempDamage;

	//mainly for later if I add a save feature
	int currFloor;
	bool bossKill;
	int x, y;
	

public:

	player(string name = "NULL") {

		currFloor = 0;
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

		currFloor = 0;

		x = 1;
		y = 1;

	}

	int getFloor() {
		return currFloor;
	}

	void advanceFloor() {
		currFloor++;
	}

	int getPX() {
		return x;
	}

	int getPY() {
		return y;
	}

	void setPX(int i) {
		x = i;
	}

	void setPY(int i) {
		y = i;
	}

	int getTempDamage() {
		return tempDamage;
	}

	void setTempDamage(int damage) {
		tempDamage = damage;
	}

	int getNormDamage() {
		return normDamage;
	}

	void setNormDamage(int damage) {
		normDamage = damage;
	}

	void nextFloor() {
		currFloor++;
	}

	bool getBossKill() {
		return bossKill;
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

	void equipAccessory(accessories* newAccess) {
		this->playerAccess = newAccess;

		switch (newAccess->getType()) {

		case accessType::HP:
			tempHP += (maxHP * 0.1);
			break;
		case accessType::MP:
			mp += (mp * 0.1);
			break;
		case accessType::Str:
			str += 5;
			break;
		case accessType::Mag:
			mag += 5;
			break;
		case accessType::End:
			end += 5;
			break;
		case accessType::Spd:
			spd += 5;
			break;
		}
	}

	void addAccessory(accessories* newAccess) {
		equipAccessory(newAccess);
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
			for (unsigned int i = 1; (i - 1) < weapons.size(); i++) {
				cout << i << ". " << weapons[(i - 1)]->getName() << " - " << weapons[(i - 1)]->outputInfo() << " Attack" << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void outputAccess() {

		//showing currently equipped armor to compare against
		cout << "Currently Equipped: " << playerAccess->getName() << " - +" << playerAccess->outputInfo() << endl << endl << "Inventory: " << endl;

		if (accessory.size() != 0) {
			for (int i = 1; (i - 1) < accessory.size(); i++) {
				cout << i << ". " << accessory[(i - 1)]->getName() << " - +" << accessory[(i - 1)]->outputInfo() << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void swapAccessory() {

		unsigned int newAccess;

		if (accessory.empty()) {
			cout << "You have no accessories to swap to." << endl;
		}
		else {

			cout << endl << "What accessory would you like to equip?" << endl;
			cin >> newAccess;


			switch (playerAccess->getType()) {

			case accessType::HP:
				tempHP -= (maxHP * 0.1);
				break;
			case accessType::MP:
				mp -= (mp * 0.1);
				break;
			case accessType::Str:
				str -= 5;
				break;
			case accessType::Mag:
				mag -= 5;
				break;
			case accessType::End:
				end -= 5;
				break;
			case accessType::Spd:
				spd -= 5;
				break;
			}

			accessory.push_back(playerAccess);
			equipAccessory(accessory[(newAccess - 1)]);
			accessory.erase(accessory.begin() + (newAccess - 1));
		}
	}

	void swapWeapons() {

		unsigned int newWeapon;

		if (weapons.empty()) {
			cout << "You have no weapon to swap to." << endl << endl;
			system("PAUSE");
		}
		else {

			cout << endl << "What weapon would you like to equip?" << endl;
			cin >> newWeapon;


			weapons.push_back(playerWeapon);
			equipWeapon(weapons[(newWeapon - 1)]);
			weapons.erase(weapons.begin() + (newWeapon - 1));
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

	int getCurEXP() {
		return curExp;
	}

	int getNeedEXP() {
		return needExp;
	}

	void playerDamage(int damage) {

			if (getHP() - damage < 0) {
				setHP(0);
			}
			else {
				setTempHP(getHP());
				setHP(getHP() - static_cast<int>(damage));
			}

	}

	int getEquipArmor() {
		return playerArmor->getArmor();
	}

	int getTempArmor() {
		return playerArmor->getTempArmor();
	}

	armor* getArmor() {
		return playerArmor;
	}

	int playerAttack(int armor) {

		int damage = (getTempDamage() + playerWeapon->getElementalDamage()) - armor;

		if (damage < 0) {
			damage = 0;
		}
		else {
			damage = damage;
		}

		setTempDamage(getNormDamage());

		return damage;
	}



	bool getGuard() {
		return guard;
	}

	void setGuard(bool flag) {
		guard = flag;
	}


	void equipWeapon(weapon* weapon) {
		playerWeapon = weapon;
		setNormDamage(playerWeapon->getDamage());
		setTempDamage(getNormDamage());
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