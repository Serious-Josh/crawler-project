//when compiling there's about a million C4244 warnings. these can be ignored, they don't have any affect on functionality

//Current Version: v0.2

/*
Authors notes:

	I had big plans to add a gui just to make doing stuff easier and make formatting a bit more pretty, but after about half a day I couldn't figure out how to output text so it's on eternal backburner for now.

	-note for myself:
		the way I might end up doing the debuff system is having enemy/player attack passed through a debuff check method which will be in the damage method
		something like: playerDamage(debuffCheck(enemyAttack(player->getArmor())))
		makes combat that much more of a nightmare, but should work decently well. will need to do the negative double checking like I have currently with -armor% and -weapon%

*/

#pragma once
#include "Menu.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include <stack>
#include "Enemy.h"
#include "Room.h"


using namespace std;


vector<vector<int>> graph;
stack<menu*>* menuStack = new stack<menu*>;
vector<room*> roomList;

vector<vector<room*>> floors;

void initializeGraph(vector<vector<int>>& graph);

int main()
{
	srand(time(NULL));

	initializeGraph(graph);
	floors.push_back(roomList);

	bool startUp = true;

	cout << "Hi there! I'm Felix and I'll be your furr-ocious feline companion on your adventure! Been a while since I've helped an adventurer, but you'll see I'm quite the cat-ch!" << endl;
	cout << "What's your name stranger?" << endl;

	string name;

	cin >> name;
	
	player* play = new player(name);

	system("CLS");

	cout << play->getName() << " huh... I'll be honest, I thought it would be much more nyarly and intimidating, but I suppose " << play->getName() << " will do. Come on!" << endl;

	play->setLocation(roomList[0]);

	system("PAUSE");
	system("CLS");

	cout << "For now the kingdom is under lockdown due to a virus that's rampaging the land, and unfur-tunately the collesium has been shut down. However, our claw-ver wizards have created something even better... An endless labyrinth! Hopefully you'll be able to spin us a might fine tail from your adventures!" << endl;

	system("PAUSE");
	system("CLS");
	
	cout << "You will be provided with a piece of starting armor, accessory, and weapon." << endl;

	system("PAUSE");
	system("CLS");


	armor* ptr = new armor;
	play->equipArmor(ptr);

	weapon* ptr2 = new weapon;
	play->equipWeapon(ptr2);


	accessories* ptrA = new accessories();
	play->addAccessory(ptrA);

	int floorCount = 0;


	do {

		if (startUp != true) {
			initializeGraph(graph);
			floors.push_back(roomList);
		}

		mMenu* main = new mMenu(play, floors[floorCount], menuStack);
		menuStack->push(main);

		menuStack->top()->displayMenu();

		if (play->getBossKill() == false) {
			menuStack->top()->displayMenu();
		}
		else {
			floorCount++;
			play->nextFloor();
			startUp = false;
		}
		
	} while (play->getBossKill() == true);


	return 0;
	
}

void initializeGraph(vector<vector<int>>& graph) {

	int roomCount = (rand() % 9) + 4;

	//adding new room objects to the room vector
	for (int i = 0; i < roomCount; i++) {
		room* newRoom = new room();
		roomList.push_back(newRoom);
	}

	//generating actual rooms
	for (int k = 0; k < roomCount; k++) {
		vector<int> newVec;

		for (int z = 0; z < roomCount; z++) {
			newVec.push_back(0);
		}

		graph.push_back(newVec);
	}

	//initializing connections
	//count is for current room
	int count = 0, count2 = 0;

	//looping through each room
	while (count < roomCount) {

		//temp is number of connections per room
		int temp = (rand() % 4) + 1;

		//checking if there's already connections
		//if so, then don't generate more connections
		for (int l = 0; l < roomCount; l++) {

			//if connection, then skip it
			if (graph[count][l] == 1) {
				count++;
				break;
			}
			else if (l == (roomCount - 1)) {

				//generating connections for each room
				for (int i = 0; i < temp; i++) {

					count2 = (rand() % roomCount);

					if (count2 != count) {

						if (graph[count][count2] == 1) {
							i--;
						}
						else {
							graph[count][count2] = 1;
							graph[count2][count] = 1;

							//picking random direction for connection
							int temp = (rand() % 4) + 1;

							//this is going to be really long condition checking
							//west
							if (temp == 1) {

								//checking if there's binary connections and if not then there we go
								if ((roomList[count]->getWest() == nullptr) && (roomList[count2]->getEast() == nullptr)) {
									roomList[count]->setWest(roomList[count2]);
									roomList[count2]->setEast(roomList[count]);
								}
								else if ((roomList[count]->getEast() == nullptr) && (roomList[count2]->getWest() == nullptr)) {
									roomList[count]->setEast(roomList[count2]);
									roomList[count2]->setWest(roomList[count]);
								}
								else if ((roomList[count]->getNorth() == nullptr) && (roomList[count2]->getSouth() == nullptr)) {
									roomList[count]->setNorth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else {
									roomList[count]->setSouth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
							}
							//east
							else if (temp == 2) {
								if ((roomList[count]->getEast() == nullptr) && (roomList[count2]->getWest() == nullptr)) {
									roomList[count]->setEast(roomList[count2]);
									roomList[count2]->setWest(roomList[count]);
								}
								else if ((roomList[count]->getWest() == nullptr) && (roomList[count2]->getEast() == nullptr)) {
									roomList[count]->setWest(roomList[count2]);
									roomList[count2]->setEast(roomList[count]);
								}
								else if ((roomList[count]->getNorth() == nullptr) && (roomList[count2]->getSouth() == nullptr)) {
									roomList[count]->setNorth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else {
									roomList[count]->setSouth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
							}
							//north
							else if (temp == 3) {
								if ((roomList[count]->getNorth() == nullptr) && (roomList[count2]->getSouth() == nullptr)) {
									roomList[count]->setNorth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else if ((roomList[count]->getSouth() == nullptr) && (roomList[count2]->getNorth() == nullptr)) {
									roomList[count]->setSouth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else if ((roomList[count]->getEast() == nullptr) && (roomList[count2]->getWest() == nullptr)) {
									roomList[count]->setEast(roomList[count2]);
									roomList[count2]->setWest(roomList[count]);
								}
								else {
									roomList[count]->setWest(roomList[count2]);
									roomList[count2]->setEast(roomList[count]);
								}
							}
							//south
							else if (temp == 4) {
								if ((roomList[count]->getSouth() == nullptr) && (roomList[count2]->getNorth() == nullptr)) {
									roomList[count]->setSouth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else if ((roomList[count]->getNorth() == nullptr) && (roomList[count2]->getSouth() == nullptr)) {
									roomList[count]->setNorth(roomList[count2]);
									roomList[count2]->setSouth(roomList[count]);
								}
								else if ((roomList[count]->getEast() == nullptr) && (roomList[count2]->getWest() == nullptr)) {
									roomList[count]->setEast(roomList[count2]);
									roomList[count2]->setWest(roomList[count]);
								}
								else {
									roomList[count]->setWest(roomList[count2]);
									roomList[count2]->setEast(roomList[count]);
								}
							}


						}

					}
				}
				count++;
				break;
			}
		}
	}
}