#pragma once
#include "Player.h"
#include "Enemy.h"
#include "Equipment.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <Windows.h>
#include <conio.h>
#include "Codes.cpp"
#include "Room.h"
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

const int MAX_X = 25;
const int MAX_Y = 25;

char render_array[MAX_Y][MAX_X]{};
char prev_render_array[MAX_Y][MAX_X]{};



class menu;

void setCursorPosition(int x, int y);
void updateScreen(char prev_buffer[][MAX_X], char curr_buffer[][MAX_X]);
void ShowConsoleCursor(bool showFlag);
int debuffCheck(boss* boss, player* play, double damage, int* debuffCount);
void renderScreen(player* play, stack<menu*>* menuSystem);





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
		cout << "3. Accessories" << endl;
		cout << "4. Exit" << endl << endl;

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
			system("CLS");
			play.outputAccess();

			cout << endl << "What would you like to do?" << endl << endl;
			cout << "Swap" << endl;
			cout << "Exit" << endl << endl;

			cin >> input1;

			if ((input1 == "Swap") || (input1 == "swap")) {
				system("CLS");
				play.outputAccess();
				play.swapAccessory();
			}

			system("CLS");
			menuSystem->top()->displayMenu();
			break;

		case 4:
			system("CLS");
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
			play->gainEXP(enem->getEXP());
			system("PAUSE");
			system("CLS");
			play->getLocation()->setEnemy(nullptr);
			play->getLocation()->setChecked();
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
						play->playerDamage(enem->enemyAttack(play->getEquipArmor()));
					}
					count = 1;
					menuSystem->top()->displayMenu();
				}
				case 2:
				{
					play->setGuard(true);
					play->playerDamage(enem->enemyAttack(play->getEquipArmor()));
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
	int count, debuffCount;
	stack<menu*>* menuSystem;
	int* dCount = &debuffCount;

public:

	bossMenu(player* player, boss* b, stack<menu*>* menuSystem) {
	
		play = player;
		bose = b;
		count = -1;
		this->menuSystem = menuSystem;

	}

	void incDebuffCount() {
		debuffCount++;
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
			bose->setTempHP(0);

			int input;

			cout << left << setw(20) << bose->getName() << setw(20) << to_string(bose->getHP()) + " HP" << endl;
			cout << left << setw(20) << play->getName() << setw(20) << to_string(play->getHP()) + " HP" << endl << endl;

			cout << "1. Attack" << endl;
			cout << "2. Guard" << endl;
			cout << "3. Enemy (View Enemy)" << endl;
			cout << "4. Inventory" << endl;

			cin >> input;
			debuffCount++;

			system("CLS");

			if (!cin || (input > 4) || (input < 1)) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "That's not a valid option. Please try again." << endl << endl;
				menuSystem->top()->displayMenu();
			}
			else {
				switch (input) {
				case 1: {
					if (bose->getHP() > 0) {
						play->playerDamage(debuffCheck(bose, play, bose->bossAttack(bose->getID(), play->getTempArmor()), dCount));

						//this is checking to see if a debuff has been applied a turn ago
						//if so, revert it
						if (debuffCount == 1) {
							play->getArmor()->setTempArmor(play->getEquipArmor());
							play->setTempDamage(play->getNormDamage());
						}

					}

					if (play->getGuard() == true) {
						play->setGuard(false);
					}

					bose->enemyDamage(play->playerAttack(bose->getArmor()));

					if (debuffCount == 1) {
						play->getArmor()->setTempArmor(play->getEquipArmor());
						play->setTempDamage(play->getNormDamage());
					}

					count = 1;
					menuSystem->top()->displayMenu();
				}

				case 2: {
					play->setGuard(true);
					play->playerDamage(debuffCheck(bose, play, bose->bossAttack(bose->getID(), play->getTempArmor()), dCount));
					count = 1;
					menuSystem->top()->displayMenu();
				}

				case 3: {
					system("CLS");
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


		//if every room is checked, then spawn boss
		//this is checked each time the main menu is called (which shouldn't be so often it causes problems)
		for (int i = 0; i < roomList.size(); i++) {

			if (roomList[i]->getCheck() == false) {
				break;
			}
			else if (i == (roomList.size() - 1) ){

				boss* newBoss = new boss(0);

				roomList[rand() % roomList.size() + 1]->setEnemy(newBoss);

				cout << "Boss has spawned. Defeat it if you dare..." << endl;
				system("PAUSE");
				system("CLS");
				
			}

		}

		renderScreen(play, menuSystem);

	}

};


int debuffCheck(boss* boss, player* play, double damage, int* debuffCount) {

	if ((damage < 0) && ((abs(damage) - abs(floor(damage))) > 0.45)) {
		
		//only player debuff
		// -1 < damage < 0 == defense debuff
		// -2 < damage < -1 == attack debuff
		if ((damage < 0) && (damage >= 0.45)) {
			play->getArmor()->setTempArmor(play->getEquipArmor() * (1 + damage));
			(*debuffCount)++;
		}
		else if ((damage <= -1) && (damage >= -2)) {
			play->setTempDamage(play->getNormDamage() * (2 + damage));
			(*debuffCount) = 0;
		}
		
		return 0;

	}
	else if (damage < 0) {

		//player debuff and attack
		if ((damage < 0) && (damage >= -1)) {
			play->getArmor()->setTempArmor(play->getEquipArmor() * (1 + damage));
			(*debuffCount) = 0;
		}
		else if ((damage <= -1) && (damage >= -2)) {
			play->setTempDamage(play->getNormDamage() * (2 + damage));
			(*debuffCount) = 0;
		}

		return damage;

	}
	else {
		return damage;
	}

}

void renderScreen(player* play, stack<menu*>* menuSystem) {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, 800, 800, TRUE);

	ShowConsoleCursor(false);

	int count = 0;

	while (count < 25) {
		for (int i = 0; i < sizeof(render_array[count]); i++) {

			//if it's on the top left
			if ((count == 0) && (i == 0)) {
				render_array[count][i] = TL;
			}

			//if it's on the top right
			else if ((count == 0) && (i == (play->getLocation()->getX() + 1))) {
				render_array[count][i] = TR;
			}

			//if it's on the top row
			else if (count == 0) {

				if (i > (play->getLocation()->getX() + 1)) {
					render_array[count][i] = ' ';
				}
				else if (i == play->getLocation()->getNDoor()) {
					render_array[count][i] = ' ';
				}
				else {

					render_array[count][i] = TB;
				}
			}

			//if it's on the bottom left corner
			else if ((count == play->getLocation()->getY() + 1) && (i == 0)) {
				render_array[count][i] = BL;
			}

			//if it's on the bottom right corner
			else if ((count == play->getLocation()->getY() + 1) && (i == (play->getLocation()->getX() + 1))) {
				render_array[count][i] = BR;
			}

			//if it's on bottom wall
			else if (count == (play->getLocation()->getY() + 1)) {

				if (i > (play->getLocation()->getX() + 1)) {
					render_array[count][i] = ' ';
				}
				else if (i == play->getLocation()->getSDoor()) {
					render_array[count][i] = ' ';
				}
				else {

					render_array[count][i] = TB;
				}
			}

			//if it's on the left wall or right wall
			else if ((i == 0) || (i == (play->getLocation()->getX() + 1))) {

				if (count > (play->getLocation()->getY() + 1)) {
					render_array[count][i] = ' ';
				}
				else if ((count == play->getLocation()->getEDoor()) && (i == play->getLocation()->getX() + 1)) {
					render_array[count][i] = ' ';
				}
				else if ((count == play->getLocation()->getWDoor()) && (i == 0)) {
					render_array[count][i] = ' ';
				}
				else {

					render_array[count][i] = LR;
				}
			}
			else {

				if (count > (play->getLocation()->getY() + 1)) {
					render_array[count][i] = ' ';
				}
				else if (i > (play->getLocation()->getX() + 1)) {
					render_array[count][i] = ' ';
				}
				else {
					render_array[count][i] = space;
				}
			}

		}

		count++;

	}

	


	render_array[play->getPY()][play->getPX()] = playIcon;

	if (play->getLocation()->getChest() == true) {
		render_array[rand() % play->getLocation()->getY() + 1][rand() % play->getLocation()->getX() + 1] = chest;
	}

	if (play->getLocation()->getEnemy() != nullptr) {

		if (play->getLocation()->getEnemy()->getBoss() == true) {
			render_array[play->getLocation()->getEnemy()->getEY()][play->getLocation()->getEnemy()->getEX()] = bossIcon;
		}
		else {
			render_array[play->getLocation()->getEnemy()->getEY()][play->getLocation()->getEnemy()->getEX()] = enemyIcon;
		}
	}

	updateScreen(prev_render_array, render_array);



	int c, ex = 0;
	while (1) {

		cout << "HP: " << play->getHP() << "     " << "MP: " << play->getMP() << "     " << "EXP: " << play->getCurEXP() << " (" << play->getNeedEXP() << ")" << endl << endl;

		c = _getch();

		if (c && c != 224) {
			cout << "Not arrow" << endl;
		}
		else {

			switch ((ex = _getch())) {
			case KEY_UP:

				//checking if the player comes into a new room
				if ((play->getPX() == play->getLocation()->getNDoor()) && (play->getPY() == 1)) {
					play->setLocation(play->getLocation()->getNorth());

					play->setPX(play->getLocation()->getSDoor());
					play->setPY(play->getLocation()->getY());

					//check to make sure player in inside room
					if (play->getPX() > play->getLocation()->getX()) {
						play->setPX(play->getLocation()->getSDoor());
					}

					if (play->getPY() > play->getLocation()->getY()) {
						play->setPY(play->getLocation()->getY());
					}


					if (play->getLocation()->getCheck() == false) {
						
						int num = rand() % 100 + 1;

						if (play->getLocation()->getCheck() == false) {

							if (num < 1) {

								enemy* newEnem = new enemy(play->getFloor());

								newEnem->setEX(rand() % play->getLocation()->getX() + 1);
								newEnem->setEY(rand() % play->getLocation()->getY() + 1);

								play->getLocation()->setEnemy(newEnem);

								renderScreen(play, menuSystem);

							}
							else if ((num < 100) && (num > 0)) {

								play->getLocation()->setChest();
							}


						}



					}

					//I think this renderScreen is obligatory since it's already called in the generateEvent function, but I'm going to leave it just in case
					renderScreen(play, menuSystem);
				}
				// isn't a new room
				else {

					if (play->getPY() > 1) {

						if (render_array[play->getPY() - 1][play->getPX()] == enemyIcon) {

							battleMenu* bMenu = new battleMenu(play, play->getLocation()->getEnemy(), menuSystem);
							menuSystem->push(bMenu);

							menuSystem->top()->displayMenu();

						}
						else if (render_array[play->getPY() - 1][play->getPX()] == chest) {

							int num = rand() % 2;

							if (num == 0) {
								armor* newArmor = new armor();

								cout << "You find " << newArmor->getName() << endl;
								system("PAUSE");
								system("CLS");
								play->addArmor(newArmor);

								play->getLocation()->setChecked();
								play->getLocation()->setChest();

							}
							else {
								weapon* ptr = new weapon();

								cout << "You find " << ptr->getName() << endl;
								system("PAUSE");
								system("CLS");
								play->addWeapon(ptr);

								play->getLocation()->setChecked();
								play->getLocation()->setChest();

							}

						}

						render_array[play->getPY() - 1][play->getPX()] = playIcon;
						render_array[play->getPY()][play->getPX()] = space;

						play->setPY(play->getPY() - 1);
						updateScreen(prev_render_array, render_array);
					}
				}

				break;

			case KEY_DOWN:

				if ((play->getPX() == play->getLocation()->getSDoor()) && (play->getPY() == play->getLocation()->getY())) {
					play->setLocation(play->getLocation()->getSouth());

					play->setPX(play->getLocation()->getNDoor());
					play->setPY(1);

					//check to make sure player in inside room
					if (play->getPX() > play->getLocation()->getX()) {
						play->setPX(play->getLocation()->getNDoor());
					}

					if (play->getPY() > play->getLocation()->getY()) {
						play->setPY(1);
					}

					if (play->getLocation()->getCheck() == false) {

						int num = rand() % 100 + 1;

						if (play->getLocation()->getCheck() == false) {

							if (num < 50) {

								enemy* newEnem = new enemy(play->getFloor());

								newEnem->setEX(rand() % play->getLocation()->getX() + 1);
								newEnem->setEY(rand() % play->getLocation()->getY() + 1);

								play->getLocation()->setEnemy(newEnem);

								renderScreen(play, menuSystem);

							}


						}
						else if ((num < 75) && (num >= 50)) {

							play->getLocation()->setChest();
						}



					}

					renderScreen(play, menuSystem);
				}
				else {

					if (render_array[play->getPY() + 1][play->getPX()] == enemyIcon) {

						battleMenu* bMenu = new battleMenu(play, play->getLocation()->getEnemy(), menuSystem);
						menuSystem->push(bMenu);

						menuSystem->top()->displayMenu();

					}
					else if (render_array[play->getPY() + 1][play->getPX()] == chest) {

						int num = rand() % 2;

						if (num == 0) {
							armor* newArmor = new armor();

							cout << "You find " << newArmor->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addArmor(newArmor);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}
						else {
							weapon* ptr = new weapon();

							cout << "You find " << ptr->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addWeapon(ptr);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}

					}

					if (play->getPY() < play->getLocation()->getY()) {
						render_array[play->getPY() + 1][play->getPX()] = playIcon;
						render_array[play->getPY()][play->getPX()] = space;

						play->setPY(play->getPY() + 1);
						updateScreen(prev_render_array, render_array);
					}
				}

				break;

			case KEY_LEFT:

				if ((play->getPY() == play->getLocation()->getWDoor()) && (play->getPX() == 1)) {

					play->setLocation(play->getLocation()->getWest());

					play->setPX(play->getLocation()->getX());
					play->setPY(play->getLocation()->getEDoor());

					if (play->getPX() > play->getLocation()->getX()) {
						play->setPX(play->getLocation()->getX());
					}

					if (play->getPY() > play->getLocation()->getY()) {
						play->setPY(play->getLocation()->getEDoor());
					}

					if (play->getLocation()->getCheck() == false) {

						int num = rand() % 100 + 1;

						if (play->getLocation()->getCheck() == false) {

							if (num < 50) {

								enemy* newEnem = new enemy(play->getFloor());

								newEnem->setEX(rand() % play->getLocation()->getX() + 1);
								newEnem->setEY(rand() % play->getLocation()->getY() + 1);

								play->getLocation()->setEnemy(newEnem);

								renderScreen(play, menuSystem);

							}


						}
						else if ((num < 75) && (num >= 50)) {

							play->getLocation()->setChest();
						}



					}

					renderScreen(play, menuSystem);

				}
				else {

					if (render_array[play->getPY()][play->getPX() - 1] == enemyIcon) {

						battleMenu* bMenu = new battleMenu(play, play->getLocation()->getEnemy(), menuSystem);
						menuSystem->push(bMenu);

						menuSystem->top()->displayMenu();

					}
					else if (render_array[play->getPY()][play->getPX() - 1] == chest) {

						int num = rand() % 2;

						if (num == 0) {
							armor* newArmor = new armor();

							cout << "You find " << newArmor->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addArmor(newArmor);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}
						else {
							weapon* ptr = new weapon();

							cout << "You find " << ptr->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addWeapon(ptr);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}

					}


					if (play->getPX() > 1) {
						render_array[play->getPY()][play->getPX() - 1] = playIcon;
						render_array[play->getPY()][play->getPX()] = space;

						play->setPX(play->getPX() - 1);
						updateScreen(prev_render_array, render_array);
					}
				}

				break;

			case KEY_RIGHT:

				if ((play->getPY() == play->getLocation()->getEDoor()) && (play->getPX() == play->getLocation()->getX())) {
					play->setLocation(play->getLocation()->getEast());

					play->setPX(1);
					play->setPY(play->getLocation()->getWDoor());

					if (play->getPX() > play->getLocation()->getX()) {
						play->setPX(1);
					}

					if (play->getPY() > play->getLocation()->getY()) {
						play->setPY(play->getLocation()->getWDoor());
					}

					if (play->getLocation()->getCheck() == false) {

						int num = rand() % 100 + 1;

						if (play->getLocation()->getCheck() == false) {

							if (num < 50) {

								enemy* newEnem = new enemy(play->getFloor());

								newEnem->setEX(rand() % play->getLocation()->getX() + 1);
								newEnem->setEY(rand() % play->getLocation()->getY() + 1);

								play->getLocation()->setEnemy(newEnem);

								renderScreen(play, menuSystem);

							}
							else if ((num < 75) && (num >= 50)) {

								play->getLocation()->setChest();

							}


						}



					}

					renderScreen(play, menuSystem);
				}
				else {

					if (render_array[play->getPY()][play->getPX() + 1] == enemyIcon) {

						battleMenu* bMenu = new battleMenu(play, play->getLocation()->getEnemy(), menuSystem);
						menuSystem->push(bMenu);

						menuSystem->top()->displayMenu();

					}
					else if (render_array[play->getPY()][play->getPX() + 1] == chest) {

						int num = rand() % 2;

						if (num == 0) {
							armor* newArmor = new armor();

							cout << "You find " << newArmor->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addArmor(newArmor);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}
						else {
							weapon* ptr = new weapon();

							cout << "You find " << ptr->getName() << endl;
							system("PAUSE");
							system("CLS");
							play->addWeapon(ptr);

							play->getLocation()->setChecked();
							play->getLocation()->setChest();

						}

					}

					if (play->getPX() < play->getLocation()->getX()) {
						render_array[play->getPY()][play->getPX() + 1] = playIcon;
						render_array[play->getPY()][play->getPX()] = space;

						play->setPX(play->getPX() + 1);
						updateScreen(prev_render_array, render_array);
					}
				}

				break;
			}
		}
	}

}



/*
HUGE HUGE shoutout to Cameron on Stackoverflow for this update code
*/
void setCursorPosition(int x, int y) {
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	cout.flush();

	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

void updateScreen(char prev_buffer[][MAX_X], char curr_buffer[][MAX_X]) {

	memset((char*)prev_render_array, 0, MAX_X * MAX_Y);

	for (int y = 0; y != MAX_Y; y++) {
		for (int x = 0; x != MAX_X; x++) {
			if (curr_buffer[y][x] == prev_buffer[y][x]) {
				continue;
			}
			setCursorPosition(x, y);
			cout << curr_buffer[y][x];
		}
	}

	cout.flush();
	memcpy((char*)prev_buffer, (char const*)curr_buffer, MAX_X * MAX_Y);

}

void ShowConsoleCursor(bool showFlag) {
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hOut, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(hOut, &cursorInfo);
}