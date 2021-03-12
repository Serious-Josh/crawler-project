#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include <iostream>
#include <iomanip>
#include <stack>


class menu {

public:

	virtual void displayMenu() = 0;

};

class inventoryMenu : public menu {

	player play;
	stack<menu*>* menuSystem;

public:

	inventoryMenu(player& player, stack<menu*>* menuSystem) {
		play = player;
		this->menuSystem = menuSystem;
	}

	void displayMenu() {

		unsigned int input, newWeap = 0, newArmor = 0;
		string input1;

		cout << "1. Weapons" << endl;
		cout << "2. Armor" << endl;
		cout << "3. Exit" << endl << endl;

		cin >> input;

		//switch statement that handles the different options
		switch (input) {
		case 1:
			system("CLS");
			play.outputWeapons();

			cout << endl << "What would you like to do?" << endl << endl;
			cout << "Swap" << endl;
			cout << "Exit" << endl << endl;

			cin >> input1;

			if ((input1 == "Swap") || (input1 == "swap")) {
				system("CLS");
				play.outputWeapons();
				play.swapWeapons();
			}

			//system("PAUSE");
			system("CLS");
			menuSystem->top()->displayMenu();
			break;


		case 2:
			system("CLS");
			play.outputArmor();

			cout << endl << "What would you like to do?" << endl << endl;
			cout << "Swap" << endl;
			cout << "Exit" << endl << endl;

			cin >> input1;

			if ((input1 == "Swap") || (input1 == "swap")) {
				system("CLS");
				play.outputArmor();
				play.swapArmor();
			}
			
			system("CLS");
			menuSystem->top()->displayMenu();
			break;
		case 3:
			menuSystem->pop();
			menuSystem->top()->displayMenu();
		}
	}



};


class battleMenu : public menu {

private:

	player* play;
	enemy* enem;
	int count;
	stack<menu*>* menuSystem;

public:

	battleMenu(player* player, enemy* enemy, stack<menu*>* menuSystem) {
		play = player;
		this->enem = enemy;
		this->menuSystem = menuSystem;
		count = 0;
	}

	void displayMenu() {


		if (play->getHP() == 0) {
			system("CLS");
			cout << "YOU DIED" << endl << endl;
			menuSystem->pop();
			exit(1);
		}
		else if (enem->getHP() == 0) {
			system("CLS");
			cout << "You defeated " << enem->getName() << "!" << endl;
			cout << "You gained " << enem->getEXP() << "exp!" << endl;
			system("PAUSE");
			system("CLS");
			menuSystem->pop();
			menuSystem->top()->displayMenu();
			return;
		}
		else {

			system("CLS");

			int temp, temp1;

			temp = (enem->getTempHP() - enem->getHP());
			temp1 = (play->getTempHP() - play->getHP());


			if (count == 1) {

				if (temp > 0) {
					cout << "You dealt " << temp << " damage!" << endl;
				}
				else {
					cout << "You dealt 0 damage!" << endl;
				}
				
				if (temp1 > 0) {
					cout << "You took " << temp1 << " damage!" << endl << endl;
				}
				else {
					cout << "You took 0 damage!" << endl;
				}

				system("PAUSE");
				system("CLS");
			}


			play->setTempHP(0);
			enem->setTempHP(0);

			play->guardFun(1);

			int input;

			ios_base::fmtflags flags = cout.flags();

			cout << left << setw(20) << enem->getName() << setw(20) << to_string(enem->getHP()) + " HP" << endl;
			cout << left << setw(20) << play->getName() << setw(20) << to_string(play->getHP()) + " HP" << endl << endl;

			cout.flags(flags);


			//cout << left << enem->getName() << setw(20) << enem->getHP() << endl;
			//cout << left << play->getName() << setw(20) << play->getHP() << endl << endl;

			cout << "1. Attack" << endl;
			cout << "2. Guard" << endl;
			cout << "3. Enemy (View Enemy)" << endl;
			cout << "4. Inventory" << endl;

			cin >> input;

			system("CLS");

			if (!cin || (input > 4) || (input < 1)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "That's not a valid option. Please try again." << endl << endl;
				menuSystem->top()->displayMenu();
			}
			else {
				switch (input) {
				case 1:
				{
					enem->enemyDamage(play->playerAttack(enem->getArmor()));
					if (enem->getHP() > 0) {
						play->playerDamage(enem->enemyAttack(play->getGuardArmor()));
					}
					count = 1;
					menuSystem->top()->displayMenu();
				}
				case 2:
				{
					play->guardFun(2);
					play->playerDamage(enem->enemyAttack(play->getGuardArmor()));
					count = 1;
					menuSystem->top()->displayMenu();
				}
				case 3:
				{
					system("CLS");
					cout << enem << endl << endl;
					system("PAUSE");
					count = 0;
					menuSystem->top()->displayMenu();
				}
				case 4:
				{
					system("CLS");
					count = 0;
					inventoryMenu* inMenu = new inventoryMenu(*play, menuSystem);
					menuSystem->push(inMenu);
					menuSystem->top()->displayMenu();
				}
				}
			}
		}

	}

};

class bossMenu : public menu {

private:

	player *play;
	boss *bose;
	int count;
	stack<menu*>* menuSystem;

public:

	bossMenu(player* player, boss* b, stack<menu*>* menuSystem) {
	
		play = player;
		bose = b;
		count = -1;
		this->menuSystem = menuSystem;

	}

	void displayMenu() {

		if (count == -1) {
			bose->enemyIntro(bose->getID());
		}

		if (play->getHP() == 0) {
			system("CLS");
			cout << "YOU DIED" << endl << endl;
			exit(0);
		}
		else if (bose->getHP() == 0) {
			system("CLS");
			cout << "You defeated " << bose->getName() << "!" << endl;
			cout << "You gained " << bose->getEXP() << "!" << endl;
			system("PAUSE");
			menuSystem->pop();
			menuSystem->top()->displayMenu();
		}
		else {

			//if it isn't a neutral turn or intro turn
			if ((count != 0) && (count != -1)) {

				int temp = (bose->getTempHP() - bose->getHP());
				int temp1 = (play->getTempHP() - play->getHP());

				cout << endl;

				if (temp1 > 0) {
					cout << "You took " << temp1 << " damage!" << endl << endl;
				}

				if (temp > 0) {
					cout << "You dealt " << temp << " damage!" << endl;
				}

			}

			play->setTempHP(0);
			bose->setTempHP(0);

			play->guardFun(1);

			int input;

			cout << left << setw(20) << bose->getName() << setw(20) << to_string(bose->getHP()) + " HP" << endl;
			cout << left << setw(20) << play->getName() << setw(20) << to_string(play->getHP()) + " HP" << endl << endl;

			cout << "1. Attack" << endl;
			cout << "2. Guard" << endl;
			cout << "3. Enemy (View Enemy)" << endl;
			cout << "4. Inventory" << endl;

			cin >> input;

			system("CLS");

			if (!cin || (input > 4) || (input < 1)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "That's not a valid option. Please try again." << endl << endl;
				menuSystem->top()->displayMenu();
			}
			else {
				switch (input) {
				case 1: {bose->enemyDamage(play->playerAttack(bose->getArmor()));
					if (bose->getHP() > 0) {
						play->playerDamage(bose->bossAttack(bose->getID(), play->getGuardArmor()));
					}
					count = 1;
					menuSystem->top()->displayMenu();
				}

				case 2: {play->guardFun(2);
					play->playerDamage(bose->bossAttack(bose->getID(), play->getGuardArmor()));
					count = 1;
					menuSystem->top()->displayMenu();
				}

				case 3: {system("CLS");
					cout << bose << endl << endl;
					system("PAUSE");
					system("CLS");
					count = 0;
					menuSystem->top()->displayMenu();
				}

				case 4: {system("CLS");
					inventoryMenu* inMenu = new inventoryMenu(*play, menuSystem);
					count = 0;
					menuSystem->push(inMenu);
					menuSystem->top()->displayMenu();
					menuSystem->pop();
					menuSystem->top()->displayMenu();
				}

				}
			}
		}
	}

};


void generateEvent(player* player, stack<menu*>* menuSystem) {

	int num = rand() % 41;

	if (player->getLocation()->getCheck() == true) {

		cout << "You have been to this room before." << endl << endl;
	}
	else {

		//chance for normal enemy
		if (num < 30) {

			player->getLocation()->setChecked();

			enemy* enem = new enemy(0);
			battleMenu* battle = new battleMenu(player, enem, menuSystem);
			menuSystem->push(battle);

			system("CLS");
			cout << "You've encountered a " << enem->getName() << "!" << endl;
			system("PAUSE");
			system("CLS");

			menuSystem->top()->displayMenu();

		}
		else if ((num > 29) && (num < 35)) {

			player->getLocation()->setChecked();

			boss* bose = new boss(0);
			bossMenu* bossM = new bossMenu(player, bose, menuSystem);
			menuSystem->push(bossM);
			system("CLS");
			menuSystem->top()->displayMenu();

		}
		else if ((num > 34) && (num < 40)) {

			player->getLocation()->setChecked();

			cout << "There is a chest in the room. Open? (Y/N)" << endl;
			string input;

			cin >> input;

			if ((input == "Y") || (input == "y")) {
				int num = rand() % 2;

				if (num == 0) {
					armor* newArmor = new armor();

					cout << "You find " << newArmor->getName() << endl;
					player->addArmor(newArmor);

				}
				else {
					weapon* ptr = new weapon();

					cout << "You find " << ptr->getName() << endl;
					player->addWeapon(ptr);

				}

				system("PAUSE");
				system("CLS");

			}
			else {

				system("CLS");

			}
		}
		else {
			system("CLS");
			cout << "There's nothing in the room." << endl;
		}
	}

}

class mMenu : public menu {

	player* play;
	vector<vector<int>> graph;
	stack<menu*>* menuSystem;
	vector<room*> roomList;

public:

	mMenu(player* player, vector<room*> roomList, stack<menu*>* menuSystem) {
		play = player;
		this->graph = graph;
		this->menuSystem = menuSystem;
		this->roomList = roomList;
	}

	void displayMenu() {

		int input;

		cout << "What would you like to do?" << endl << endl;

		cout << "1. Move Rooms" << endl;
		cout << "2. Status" << endl;
		cout << "3. Quit Game" << endl;

		cin >> input;

		system("CLS");

		if (!cin || input < 1 || input > 3) {
			cin.ignore();
			cin.clear(1000, 'n');
			cout << "That's not a valid option. Please try again." << endl;
			menuSystem->top()->displayMenu();
		}

		switch (input) {

			//move rooms
		case 1:
		{
			play->moveLocation(roomList);
			generateEvent(play, menuSystem);
			menuSystem->top()->displayMenu();
		}

		//quit game
		case 2: 
		{
			cout << play << endl;
			system("PAUSE");
			system("CLS");
			menuSystem->top()->displayMenu();
		}
		case 3: {
			exit(0);
		}
		}


		if ((play->getHP() > 0) && input != 3) {
			play->setMaxHP(play->getMaxHP());
		}
		else {
			return;
		}

	}

};