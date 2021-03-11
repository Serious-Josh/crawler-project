//too lazy to actually change project name, so dataStructures_finalProject it will remain even though it's now a personal project

#pragma once
#include "Menu.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Player.h"
#include <stack>
#include "Enemy.h"

using namespace std;

vector<vector<int>> graph;
stack<menu*> menuStack;

void initializeGraph(vector<vector<int>>& graph) {

	int roomCount = (rand() % 9) + 4;

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
							}

						}
				}
				count++;
				break;
			}
		}
	}
}



int main()
{
	srand(time(NULL));

	initializeGraph(graph);

	cout << "Hi there! I'm Felix and I'll be your furr-ocious feline companion on your adventure! Been a while since I've helped an adventurer, but you'll see I'm quite the cat-ch!" << endl;
	cout << "What's your name stranger?" << endl;

	string name;

	cin >> name;
	
	player* play = new player();

	play->setName(name);

	system("CLS");

	cout << play->getName() << " huh... I'll be honest, I thought it would be much more nyarly and intimidating, but I suppose " << play->getName() << " will do. Come on!" << endl;

	system("PAUSE");
	system("CLS");

	cout << "For now the kingdom is under lockdown due to a virus that's rampaging the land, and unfur-tunately the collesium has been shut down. However, our claw-ver wizards have created something even better... An endless labyrinth! Hopefully you'll be able to spin us a might fine tail from your adventures!" << endl;

	system("PAUSE");
	system("CLS");


	//example for how to create new  equipment and how to equip them
	//they can be added to a players inventory through the player.addWeapon(armor*) / player.adArmor(armor*) functions
	armor* ptr = new armor;
	play->equipArmor(ptr);

	weapon* ptr2 = new weapon;
	play->equipWeapon(ptr2);
	weapon* ptr3 = new weapon;
	play->addWeapon(ptr3);

	mMenu* main = new mMenu(play, graph, menuStack);
	menuStack.push(main);
	menuStack.top()->displayMenu();

	//mainMenu(player);

	return 0;
	
}