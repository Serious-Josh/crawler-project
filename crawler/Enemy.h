#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Equipment.h"


using namespace std;

class enemy {
private:
	string name;
	int area, hp, tempHP = 0, level, exp, attack, armor, tempArmor = 0;
	bool boss = false;
	int x = NULL, y = NULL;

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
			armor = attack / 8;

			boss = false;
		}

		int tempx = rand() % 100 + 1;

		switch (area)
		{
		case 0: 
				if (tempx < 21) {
					name = "Rock Man";
					armor = armor * 1.4;
					break;
				}
				else if ((tempx < 41) && (tempx >= 21)) {
					name = "Dire Rat";
					attack = attack * 1.2;
					hp = hp / 1.4;
					break;
				}
				else if ((tempx < 61) && (tempx >= 41)) {
					name = "Flying Squirrel";
					hp = hp / 1.2;
					break;
				}
				else if ((tempx < 81) && (tempx >= 61)) {
					name = "Slime";
					break;
				}
				else {
					name = "Goblin";
					hp = hp / 1.3;
					attack = attack * 1.2;
					armor = armor * 1.2;
					break;
				}
		case 1:
			if (tempx < 21) {
				name = "Rogue Knight";
				hp = hp * 1.4;
				armor = armor * 1.3;
				attack = attack / 1.2;
				break;
			}
			else if ((tempx < 41) && (tempx >= 21)) {
				name = "Imperial Soldier";
				attack = attack * 1.2;
				break;
			}
			else if ((tempx < 61) && (tempx >= 41)) {
				name = "Bandit";
				break;
			}
			else if ((tempx < 81) && (tempx >= 61)) {
				name = "Assassin";
				armor = armor / 1.4;
				hp = hp / 1.4;
				attack = attack * 1.6;
				break;
			}
			else {
				name = "Pyromancer";
				attack = attack * 1.2;
				armor = armor / 1.5;
				break;
			}
		//case 2:

		}

	}

	void setEX(int i) {
		x = i;
	}

	void setEY(int i) {
		y = i;
	}

	int getEX() {
		return x;
	}

	int getEY() {
		return y;
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
//list = cave bear, tower knight, 
enum class bosses{Bear, TK, NN, Treant, Titania, MM, Shreek, FK, None};

class boss : public enemy {
private:
	bosses id = bosses::None;
	bool enrageCheck = false;
	bool isBoss = true;

	//used for any boss mechanics or whatnot
	bool extraCheck = false;

public:

	boss(int area) : enemy(area) {

		int temp = rand() % 48 + 1;

		switch (area) {
		case 0:
			//cave bear

			setName("Cave Bear");
			setLevel(11);
			setHP(465);
			setAttack(45);
			setArmor(18);
			setType(bosses::Bear);
			setEXP(10 * (pow(1.5, (getLevel() / 5.5))));
			break;
		case 1:

			//tower knight

			setName("Tower Knight");
			setLevel(15);
			setHP(800);
			setAttack(60);
			setArmor(32);
			setType(bosses::TK);
			setEXP(10 * (pow(1.5, (getLevel() / 5.5))));
			break;
		//case 2:
		}

		setTempArmor(getArmor());

		setBoss(true);

	}

	double bossAttack(bosses id, int tempArmor) {

		setArmor(getTempArmor());
		int temp = rand() % 100 + 1;

		switch (id) {
		case bosses::Bear: 
			if (temp < 31) {
				//slash attack
				//deals 35% more damage, but lowers boss armor by 20%
				cout << "The Bear Slashes at you with it's huge claws! " << endl;
				setArmor(getTempArmor());
				setTempArmor(getArmor());
				setArmor(getArmor() * 0.8);
				return (enemyAttack(tempArmor) * 1.35);
			}
			else if ((temp < 56) && (temp >= 31)) {
				//roar attack
				//lowers the player armor by 20%
				cout << "The Bear roars wildly, piercing the calm of battle and rattling you! " << endl;
				setArmor(getTempArmor());
				return -0.2;
			}
			else {
				//normal attack ezpz
				cout << "The bear snaps at you with it's large maw!" << endl;
				setArmor(getTempArmor());
				return enemyAttack(tempArmor);
			}
			break;

		case bosses::TK:

			if (getHP() <= 400) {
				//enrage

				if ((enrageCheck == false) && ((getHP() <= 400) && (getHP() >200))) {
					cout << "The Tower Knight roars in anger, throwing his shield to the side and wielding his greatsword in both hands!" << endl << endl;
					enrageCheck = true;
					system("PAUSE");
					system("CLS");
				}

				if (temp > 51) {
					//sword slam
					//deals 45% more damage
					cout << "The Tower Knight pulls back his sword and slams it down on you with immense force!" << endl;
					setArmor(getTempArmor());
					return enemyAttack(tempArmor) * 1.45;
				}
				else {
					//leg sweep
					//lowers player attack by 35%
					cout << "The Tower Knight sweeps his sword low to the ground, hitting your legs and knocking you off balance." << endl;
					setArmor(getTempArmor());
					return -1.35;
				}

				//second enrage
				if (getHP() <= 200) {
					if (enrageCheck == true) {
						cout << "The Tower Knight throws his sword to the side and readies himself for unarmed combat!" << endl;
						enrageCheck = false;
						system("PAUSE");
						system("CLS");

						//add system where player can also go unarmed for increased exp yield

					}

					if ((temp > 31) && (extraCheck == false)) {
						//focus
						//increases next attack damage by 65%

						cout << "The Tower Knight slightly relaxes... a menacing aura is emanating from him..." << endl;
						extraCheck = true;
						return 0;
					}
					else {
						//power hit

						cout << "The Tower Knight reels back his first and hurls it at you with extreme speed and power!" << endl;

						if (extraCheck == true) {
							return enemyAttack(tempArmor) * 1.85;
						}
						else {
							return enemyAttack(tempArmor) * 1.2;
						}
					}
				}

			}

			if (temp > 70) {
				//shield slam
				//deals 15% more damage and increases boss armor by 15%
				cout << "The Tower Knight slams down his shield on you!" << endl;
				setArmor(getTempArmor());
				setTempArmor(getArmor());
				setArmor(getArmor() * 1.15);
				return enemyAttack(tempArmor) * 1.15;
			}
			else if ((temp > 50) && (temp <= 70)) {
				//defense curl
				//increases armor by 65%
				cout << "The Tower Knight raises his shield to protect himself!" << endl;
				setArmor(getTempArmor());
				setTempArmor(getArmor());
				setArmor(getArmor() * 1.65);
				return 0;
			}
			else {
				//normal attack
				setArmor(getTempArmor());
				return enemyAttack(tempArmor);
			}
		}
	}

		void enemyIntro(bosses boss) {

			switch (boss) {
			
			case bosses::Bear:
				cout << "You approach the mouth of a cave. You can hear low grumblings come from within... Suddenly a large ball of fur and fury erupts from the opening in the rock: a Cave Bear!" << endl << endl;
				break;

			case bosses::TK:
				cout << "You approach a huge statue of a knight guarding the exit door. As you step closer the statue suddenly begins to move! Wielding a greatsword and tower shield, the now living Tower Knight readies himself for combat!" << endl << endl;
				break;
			}

		}

		bosses getID() {
			return id;
		}

		void setType(bosses type) {
			id = type;
		}

		bool getBoss() {
			return isBoss;
		}

};