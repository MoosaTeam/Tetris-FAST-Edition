#include "PurpleTile.h"

// constructor
PurpleTile::PurpleTile() {

	pos = new pair<int, int>[4];

	// adding the inital positions for the whole block
	for (int ind = 0, j = 3; j <= 5; ind++, j++) {
		pos[ind].first = 0;
		pos[ind].second = j;
	}

	pos[3].first = 1;
	pos[3].second = 4;

}

// function to rotate the block
void PurpleTile::rotate(int**& grid, int rows, int cols) {

	pair<int, int>* tempPos = new pair<int, int>[4];

	// for 90 degrees rotation
	if (rotation == 0) {

		for (int i = 0; i < 3; i++) {
			tempPos[i].first = pos[1].first + i - 1;
			tempPos[i].second = pos[1].second;
		}
		tempPos[3].first = pos[0].first;
		tempPos[3].second = pos[0].second;
		
		if (tempPos[0].first < 0)
			move(tempPos, "down");

	}

	// for 180 degrees rotation
	else if (rotation == 1) {
		for (int i = 0; i < 3; i++) {
			tempPos[i].first = pos[1].first;
			tempPos[i].second = pos[1].second - i + 1;
		}
		tempPos[3].first = pos[0].first;
		tempPos[3].second = pos[0].second;

		if (tempPos[0].second > cols - 1) {
			move(tempPos, "left");
		}

	}
	
	// for 270 degrees rotation
	else if (rotation == 2) {

		for (int i = 0; i < 3; i++) {
			tempPos[i].first = pos[1].first - i + 1;
			tempPos[i].second = pos[1].second;
		}
		tempPos[3].first = pos[0].first;
		tempPos[3].second = pos[0].second;

		if (tempPos[0].first > rows - 1) {
			move(tempPos, "up");
		}

	}

	// for 360 degrees rotation
	else if (rotation == 3) {

		for (int i = 0; i < 3; i++) {
			tempPos[i].first = pos[1].first;
			tempPos[i].second = pos[1].second + i - 1;
		}
		tempPos[3].first = pos[0].first;
		tempPos[3].second = pos[0].second;

		if (tempPos[0].second < 0)
			move(tempPos, "right");

		rotation = -1;

	}

	// checking for block boundaries
	bool check = false;
	while (!check) {
		check = true;
		for (int i = 0; i < 4; i++) {
			int x = tempPos[i].first;
			int y = tempPos[i].second;
			if (!find({ x, y }) && grid[x][y] != 0) {
				delete[] tempPos;
				return;
			}

		}
	}

	// adding onto the grid
	int temp = grid[pos[0].first][pos[1].second];
	for (int i = 0; i < 4; i++) {
		int x = pos[i].first;
		int y = pos[i].second;
		grid[x][y] = 0;
	}
	for (int i = 0; i < 4; i++) {
		int x = tempPos[i].first;
		int y = tempPos[i].second;
		grid[x][y] = temp;
	}
	delete[] pos;
	pos = tempPos;

	rotation++;



}
