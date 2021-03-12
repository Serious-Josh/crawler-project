#pragma once

class room {

private:

	//list of connections
	room* west;
	room* east;
	room* north;
	room* south;
	bool checked;

public:

	room() {
		west = nullptr;
		east = nullptr;
		north = nullptr;
		south = nullptr;
		checked = false;
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