#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "Equipment.h"

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
	vector<vector<equipment*>> inventory;
	weapon* playerWeapon;
	armor* playerArmor;

	//going to need to do some messing around to keep this to the room number and not a pointer to the vector since the vector doesn't asy which room it is
	int location;
	

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


		//inventory initialization
		vector<equipment*> weapons;
		vector<equipment*> armor;

		inventory.push_back(weapons);
		inventory.push_back(armor);

	}

	//returns the room number the player is in
	int getLocation() {
		return location;
	}

	void displayPlayerBattle() {
		cout << getName() << " --- " << getHP() << " HP" << endl << endl;
	}

	void setLocation(int location) {
		this->location = location;
	}

	void moveLocation(const vector<vector<int>>& graph) {

		cout << "Which room do you want to room to: " << endl;

		vector<int> rooms;
		int count = 1;

		for (int i = 0; i < graph[getLocation()].size(); i++) {

			if (graph[location][i] == 1) {
				cout << count << ". " << i << endl;
				rooms.push_back(i);
				count++;
			}
		}

		cout << endl;

		int input;
		cin >> input;

		setLocation(rooms[input - 1]);
		
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

	//getter function block
	void outputWeapons() {
		vector<equipment*> temp = inventory[0];

		//showing currently equipped armor to compare against
		cout << "Currently Equipped: " << playerWeapon->getName() << " - " << playerWeapon->getDamage() << " Attack" << endl << endl << "Inventory: " << endl;

		if (temp.size() != 0) {
			for (int i = 1; (i - 1) < temp.size(); i++) {
				cout << i << ". " << temp[(i - 1)]->getName() << " - " << temp[(i - 1)]->outputInfo() << " Attack" << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void outputArmor() {
		vector<equipment*> temp = inventory[1];
		
		//showing currently equipped armor to compare against
		cout << "Currently Equipped: " << playerArmor->getName() << " - " << playerArmor->getArmor() << " Armor" << endl << endl << "Inventory: " << endl;


		if (temp.size() != 0) {
			for (int i = 1; (i - 1) < temp.size(); i++) {
				cout << i << ". " << temp[(i - 1)]->getName() << " - " << temp[(i - 1)]->outputInfo() << " Armor" << endl;
			}
		}
		else {
			cout << "You have nothing else in your inventory." << endl;
		}
	}

	void addWeapon(weapon* weapon) {
		inventory[0].push_back(weapon);
	}

	void addArmor(armor* armor) {
		inventory[1].push_back(armor);
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

ostream& operator<<(ostream& os, player& player) {
	os << player.getName() << endl << "Level: " << player.getLevel() << endl << "HP: " << player.getHP() << endl << "MP: " << player.getMP() << endl << endl << "Strength: " << player.getStr() << endl << "Magic: " << player.getMag() << endl;
	os << "Speed: " << player.getSpd() << endl << "Endurance: " << player.getEnd() << endl;

	return os;
}