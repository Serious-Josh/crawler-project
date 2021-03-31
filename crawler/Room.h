#pragma once

#include "Enemy.h"

class room {

private:

	//list of connections
	room* west;
	room* east;
	room* north;
	room* south;
	bool checked;
	bool hasChest;

	enemy* enem;

	//actual size of the rooms that you can walk around in
	int x, y;
	int wDoor, eDoor, nDoor, sDoor;

public:

	room() {
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		checked = false;

		wDoor = NULL;
		eDoor = NULL;
		nDoor = NULL;
		sDoor = NULL;

		x = rand() % 17 + 7;
		y = rand() % 17 + 7;

	}

	bool getChest() {
		return hasChest;
	}

	void setChest() {
		if (hasChest == true) {
			hasChest = false;
		}
		else {
			hasChest = true;
		}
	}

	//sets the location of the door to the connecting room. do after connections are set up
	void setDoors() {

		if (west != nullptr) {
			int loc = rand() % y + 1;
			wDoor = loc;

			west->setEDoor(rand() % west->getY() + 1);

		}
		else if (east != nullptr) {

			int loc = rand() % y + 1;
			eDoor = loc;

			east->setWDoor(rand() % east->getY() + 1);

		}
		else if (north != nullptr) {

			int loc = rand() % x + 1;
			nDoor = loc;

			north->setSDoor(rand() % north->getX() + 1);

		}
		else if(south != nullptr){

			int loc = rand() % x + 1;
			sDoor = loc;

			south->setNDoor(rand() % south->getX() + 1);
		}

	}

	void setEnemy(enemy* enemi) {
		enem = enemi;
	}

	enemy* getEnemy() {
		return enem;
	}

	int getWDoor() {
		return wDoor;
	}

	int getEDoor() {
		return eDoor;
	}

	int getNDoor() {
		return nDoor;
	}

	int getSDoor() {
		return sDoor;
	}

	void setWDoor(int i) {
		wDoor = i;
	}

	void setEDoor(int i) {
		eDoor = i;
	}

	void setNDoor(int i) {
		nDoor = i;
	}

	void setSDoor(int i) {
		sDoor = i;
	}

	int getX() {
		return x;
	}

	int getY() {
		return y;
	}

	void setWest(room* room) {
		west = room;
	}

	void setEast(room* room) {
		east = room;
	}

	void setNorth(room* room) {
		north = room;
	}

	void setSouth(room* room) {
		south = room;
	}

	void setChecked() {
		checked = true;
	}

	room* getWest() {
		return west;
	}

	room* getEast() {
		return east;
	}

	room* getNorth() {
		return north;
	}

	room* getSouth() {
		return south;
	}

	bool getCheck() {
		return checked;
	}
};