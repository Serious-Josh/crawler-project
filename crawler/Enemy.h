#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Equipment.h"
#include "Player.h"


using namespace std;

class enemy {
private:
	string name;
	int area, hp, tempHP = 0, level, exp, attack, armor, tempArmor = 0;
	bool boss = false;

public:

	enemy(int area) {

		this->area = area;

		int levelTemp, temp, temp2;

		//calculating the 
		levelTemp = 10 * pow(area, (area / sqrt(area)));

		//adding in some variation to the randomness
		//just cause
		temp = rand() % 2;
		if (temp == 0) {
			temp2 = -1;
		}
		else {
			temp2 = 1;
		}

		if (area == 0) {
			//this is for area 1
			//levels range from 2 to 7
			//is mostly used for early game/tutorial
			level = rand() % 4 + 3;

			hp = level * 12;
			attack = (1 / 1.3) * pow(level, 2);
			armor = attack / 8;
			exp = level * 1.7;
		}
		else {

			//calculating the level by taking a random number within a range and adding the level onto it
			level = rand() % (7 + temp2) + levelTemp;

			//the domain of the level function is x > 10, so this is to safeguard against that
			if (level < 11) {
				level = 11;
			}

			int hpTemp = 0;
			hpTemp = (pow(level, 2.7)) / ((level / (level - 10)) * sqrt(level)) + 200;

			//calculating hp based on the hp function and base scaling dependent on the area
			hp = (rand() % (200 * area)) + hpTemp;

			//exp based on level
			//don't want it to be random because that would add too much variability imo
			exp = level * 1.7;

			//attack is a function of level
			//sort of a steep curve so around level 70 attack will be ~3750
			attack = (1 / 1.3) * pow(level, 2);

			//armor is a function of attack. no crazy calculations, very straightforward
			armor = attack / 8 ;

			boss = false;
		}

		int tempx = rand() % 100 + 1;

		switch (area)
		{
		case 0: if (tempx < 33) {
			setName("Rock Man");
		}
			  else if ((tempx < 66) && (tempx >= 33)) {
			setName("Rock Wall");
		}
			  else {
			setName("Flying Squirrel");
		}
			break;
		}

	}


	string getName() {
		return name;
	}

	int getHP() {
		return hp;
	}

	int getLevel() {
		return level;
	}

	int getEXP() {
		return exp;
	}

	int getAttack() {
		return attack;
	}

	int getArmor() {
		return armor;
	}

	void setHP(int num) {
		hp = num;
	}

	void setName(string name) {
		this->name = name;
	}

	void setLevel(int level) {
		this->level = level;
	}

	void setAttack(int attack) {
		this->attack = attack;
	}

	void setArmor(int armor) {
		this->armor = armor;
	}

	void setEXP(int exp) {
		this->exp = exp;
	}

	int enemyAttack(int armor) {
		int damage = (getAttack() - (armor / 2));

		if (damage < 0) {
			damage = 0;
		}
		else {
			damage = damage;
		}

		return damage;
	}

	void enemyDamage(int damage) {
		if (getHP() - damage < 0) {
			setHP(0);
		}
		else {
			setTempHP(getHP());
			setHP(getHP() - damage);
		}
	}

	void setTempArmor(int armor) {
		tempArmor = armor;
	}

	int getTempArmor() {
		return tempArmor;
	}

	bool getBoss() {
		return boss;
	}

	void setBoss(bool flag) {
		boss = flag;
	}

	int getTempHP() {
		return tempHP;
	}

	void setTempHP(int hp) {
		tempHP = hp;
	}

};

ostream& operator<<(ostream& os, enemy* enemy) {
	os << enemy->getName() << endl << "Level: " << enemy->getLevel() << endl << "HP: " << enemy->getHP() << endl << endl;

	return os;
}


//for bosses attack is just a foundation which is adjusted for different moves/mechanics
//normal attacks will be slightly lower attack than the base attack while other moves will be stronger/weaker depending on the specific mech

enum class bosses{Bear, Grog, NN, Treant, Titania, MM, Shreek, FK, None};

class boss : public enemy {
private:
	bosses id = bosses::None;

public:

	boss(int area) : enemy(area) {

		int temp = rand() % 48 + 1;

		switch (area) {
		case 0:
			if (temp < 50) {
				//cave bear

				setName("Cave Bear");
				setLevel(11);
				setHP(465);
				setAttack(45);
				setArmor(18);
				setType(bosses::Bear);
				setEXP(10 * (pow(1.5, (getLevel() / 5.5))));

			}
			else {
				//Grog

				//setName("Grog");
			}
		}

		setTempArmor(getArmor());

		setBoss(true);

	}

	int bossAttack(bosses id, int playerArmor) {

		setArmor(getTempArmor());
		int temp = rand() % 100 + 1;

		switch (id) {
		case bosses::Bear: if (temp > 70) {
			//slash attack
			//deals 35% more damage, but lowers boss armor by 20%
			cout << "The Bear Slashes at you with it's huge claws! ";
			setArmor(getTempArmor());
			setTempArmor(getArmor());
			setArmor(getArmor() * 0.8);
			return enemyAttack(playerArmor) * 1.35;
		}
						 else if ((temp > 50) && (temp <= 70)) {
			//roar attack
			//lowers the player armor by 20%
			cout << "The Bear roars wildly, piercing the calm of battle and rattling you! ";
			setArmor(getTempArmor());
			return -1;
		}
						 else {
			//normal attack ezpz
			setArmor(getTempArmor());
			return enemyAttack(playerArmor);
		}
		}
	}

		void enemyIntro(bosses boss) {

			switch (boss) {
			case bosses::Bear: cout << "You approach the mouth of a cave. You can hear low grumblings come from within... Suddenly a large ball of fur and fury erupts from the opening in the rock: a Cave Bear!" << endl << endl;
			}

		}

		bosses getID() {
			return id;
		}

		void setType(bosses type) {
			id = type;
		}

};