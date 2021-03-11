#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include <iostream>
#include <stack>


class menu {

public:

	//so for some reason when this function plays, it pops the menuSystem, for god knows what reason
	virtual void displayMenu() = 0;

};

class inventoryMenu : public menu {

	player play;
	stack<menu*> menuSystem;

public:

	inventoryMenu(player& player, const stack<menu*> menuSystem) {
		play = player;
		this->menuSystem = menuSystem;
	}

	void displayMenu() {

		int input;

		cout << "1. Weapons" << endl;
		cout << "2. Armor" << endl;
		cout << "3. Exit" << endl << endl;

		cin >> input;

		//switch statement that handles the different options
		switch (input) {
		case 1: 			system("CLS");
			play.outputWeapons();
			system("PAUSE");
			system("CLS");

			menuSystem.top()->displayMenu();

		case 2:				system("CLS");
			play.outputArmor();
			system("PAUSE");
			system("CLS");
			menuSystem.top()->displayMenu();
		case 3:	menuSystem.pop();
			break;
		}
	}

};


class battleMenu : public menu {

private:

	player play;
	enemy enem;
	int count;
	stack<menu*> menuSystem;

public:

	battleMenu(player player, enemy enemy, int count, stack<menu*> menuSystem) {
		play = player;
		this->enem = enemy;
		this->count = count;
		this->menuSystem = menuSystem;
	}

	void displayMenu() {


		if (play.getHP() == 0) {
			system("CLS");
			cout << "YOU DIED" << endl << endl;
			menuSystem.pop();
			exit(1);
		}
		else if (enem.getHP() == 0) {
			system("CLS");
			cout << "You defeated " << enem.getName() << "!" << endl;
			cout << "You gained " << enem.getEXP() << "exp!" << endl;
			system("PAUSE");
			system("CLS");
			menuSystem.top()->displayMenu();
			return;
		}
		else {

			system("CLS");

			int temp, temp1;

			temp = (enem.getTempHP() - enem.getHP());
			temp1 = (play.getTempHP() - enem.getHP());


			if ((count != 0) && (count != -1)) {

				if (temp > 0) {
					cout << "You dealt " << to_string(temp) << " damage!" << endl;
				}
				else if (temp1 > 0) {
					cout << "You took " << temp1 << " damage!" << endl << endl;
				}
			}


			play.setTempHP(0);
			enem.setTempHP(0);

			play.guardFun(1);

			int input;

			play.displayPlayerBattle();

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
				menuSystem.top()->displayMenu();
			}
			else {
				switch (input) {
				case 1:
				{
					enem.enemyDamage(play.playerAttack(enem.getArmor()));
					if (enem.getHP() > 0) {
						play.playerDamage(enem.enemyAttack(play.getGuardArmor()));
					}
					battleMenu* newBat = new battleMenu(play, enem, 1, menuSystem);
					menuSystem.push(newBat);
					menuSystem.top()->displayMenu();
				}
				case 2:
				{
					play.guardFun(2);
					play.playerDamage(enem.enemyAttack(play.getGuardArmor()));
					battleMenu* newBat = new battleMenu(play, enem, 1, menuSystem);
					menuSystem.push(newBat);
					menuSystem.top()->displayMenu();
				}
				case 3:
				{
					system("CLS");
					cout << enem << endl << endl;
					system("PAUSE");
					battleMenu* newBat = new battleMenu(play, enem, 0, menuSystem);
					menuSystem.push(newBat);
					menuSystem.top()->displayMenu();
				}
				case 4:
				{
					system("CLS");
					//for whatever reason I was stuck troubleshooting because I forgot I had to make it a pointer to pass it to a stack that holds pointers :/
					battleMenu* newBat = new battleMenu(play, enem, 0, menuSystem);
					menuSystem.push(newBat);
					inventoryMenu* inMenu = new inventoryMenu(play, menuSystem);
					menuSystem.push(inMenu);
					menuSystem.top()->displayMenu();
					cout << endl << endl;
					system("PAUSE");
					menuSystem.top()->displayMenu();
				}
				}
			}
		}

	}

};

class bossMenu : public menu {

private:

	player play;
	boss bose;
	int count;
	stack<menu*> menuSystem;

public:

	bossMenu(player player, boss b, int count, stack<menu*> menuSystem) {
	
		play = player;
		bose = b;
		this->count = count;
		this->menuSystem = menuSystem;

	}

	void displayMenu() {

		if (count == -1) {
			bose.enemyIntro(bose.getID());
		}

		if (play.getHP() == 0) {
			system("CLS");
			cout << "YOU DIED" << endl << endl;
			exit(0);
		}
		else if (bose.getHP() == 0) {
			system("CLS");
			cout << "You defeated " << bose.getName() << "!" << endl;
			cout << "You gained " << bose.getEXP() << "!" << endl;
			system("PAUSE");
			menuSystem.pop();

		}
		else {

			if ((count != 0) && (count != -1)) {
				if ((bose.getTempHP() - bose.getHP()) > 0) {
					cout << "You dealt " << play.playerAttack(bose.getTempArmor()) << " damage!" << endl;
				}

				if ((play.getTempHP() - play.getHP()) > 0) {
					cout << "You took " << (play.getTempHP() - play.getHP()) << " damage!" << endl << endl;
				}
			}

			play.setTempHP(0);
			bose.setTempHP(0);

			play.guardFun(1);

			int input;

			play.displayPlayerBattle();

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
				menuSystem.top()->displayMenu();
			}
			else {
				switch (input) {
				case 1: {bose.enemyDamage(play.playerAttack(bose.getArmor()));
					if (bose.getHP() > 0) {
						play.playerDamage(bose.bossAttack(bose.getID(), play.getGuardArmor()));
					}

					bossMenu* newBoss = new bossMenu(play, bose, 1, menuSystem);
					menuSystem.pop();
					menuSystem.push(newBoss);
					menuSystem.top()->displayMenu();
				}

				case 2: {play.guardFun(2);
					play.playerDamage(bose.bossAttack(bose.getID(), play.getGuardArmor()));

					bossMenu* newBoss1 = new bossMenu(play, bose, 1, menuSystem);
					menuSystem.pop();
					menuSystem.push(newBoss1);
					menuSystem.top()->displayMenu();
				}

				case 3: {system("CLS");
					cout << bose << endl << endl;
					system("PAUSE");
					system("CLS");

					bossMenu* bMenu = new bossMenu(play, bose, 0, menuSystem);
					menuSystem.push(bMenu);
					menuSystem.top()->displayMenu();
				}

				case 4: {system("CLS");
					inventoryMenu* invMenu = new inventoryMenu(play, menuSystem);
					menuSystem.push(invMenu);
					menuSystem.top()->displayMenu();
				}
				}
			}
		}
	}

};


void generateEvent(player player, stack<menu*> menuSystem) {

	int num = rand() % 41;

	//chance for normal enemy
	if (num < 30) {
		enemy enemy(0);
		battleMenu* battle = new battleMenu(player, enemy, 0, menuSystem);

		menuSystem.push(battle);
		menuSystem.top()->displayMenu();

	}
	else if ((num > 29) && (num < 35)) {
		boss boss(0);
		bossMenu* bossM = new bossMenu(player, boss, 0, menuSystem);

		menuSystem.push(bossM);
		menuSystem.top()->displayMenu();

	}
	else if((num > 34) && (num < 40)) {
		cout << "There is a chest in the room. Open? (Y/N)" << endl;
		string input;

		cin >> input;

		if ((input == "Y") || (input == "y")) {
			int num = rand() % 2;

			if (num == 0) {
				armor* newArmor = new armor();

				cout << "You find " << newArmor->getName() << endl;
				player.addArmor(newArmor);

			}
			else {
				weapon* ptr = new weapon();

				cout << "You find " << ptr->getName() << endl;
				player.addWeapon(ptr);

			}

			system("PAUSE");
			system("CLS");

		}
		else {

			system("CLS");

		}
	}
	else {
		cout << "There's nothing in the room." << endl;
	}

}

class mMenu : public menu {

	player play;
	vector<vector<int>> graph;
	stack<menu*> menuSystem;

public:

	mMenu(player player, vector<vector<int>> graph, const stack<menu*> menuSystem) {
		play = player;
		this->graph = graph;
		this->menuSystem = menuSystem;
	}

	void displayMenu() {

		int input;

		cout << "You are currently in room " << play.getLocation() << ". What would you like to do?" << endl << endl;

		cout << "1. Move Rooms" << endl;
		cout << "2. Quit Game" << endl;

		cin >> input;

		system("CLS");

		if (!cin || input < 1 || input > 2) {
			cin.ignore();
			cin.clear(1000, 'n');
			cout << "That's not a valid option. Please try again." << endl;
			menuSystem.top()->displayMenu();
		}

		switch (input) {
		case 1:
		{
			play.moveLocation(graph);
			generateEvent(play, menuSystem);
			mMenu* m = new mMenu(play, graph, menuSystem);
			menuSystem.push(m);
			mMenu* m1 = new mMenu(play, graph, menuSystem);
			menuSystem.push(m1);
			menuSystem.top()->displayMenu();
		}
		case 2: exit(0);
		}


		if ((play.getHP() > 0) && input != 3) {
			play.setMaxHP(play.getMaxHP());
		}
		else {
			return;
		}

	}

};