#include "RedTile.h"

// constructor
RedTile::RedTile() {

	pos = new pair<int, int>[4];

	// defining the initial positions of the whole block
	for (int ind = 0, j = 3; j <= 4; ind++, j++) {
		pos[ind].first = 0;
		pos[ind].second = j;
	}

	for (int ind = 2, j = 4; j <= 5; ind++, j++) {
		pos[ind].first = 1;
		pos[ind].second = j;
	}

}

// function to rotate the block
void RedTile::rotate(int**& grid, int rows, int cols) {

	pair<int, int>* tempPos = new pair<int, int>[4];

	// for 90 degrees rotation
	if (rotation == 0) {

		for (int i = 0; i < 2; i++) {
			tempPos[i].first = pos[3].first + i - 1;
			tempPos[i].second = pos[3].second;
		}
		for (int i = 2; i < 4; i++) {
			tempPos[i].first = pos[2].first + i - 2;
			tempPos[i].second = pos[2].second;
		}

		if (tempPos[3].first > rows - 1) {
			move(tempPos, "up");
		}

	}
	// for 180 degrees rotation
	else if (rotation == 1) {
		for (int i = 0; i < 2; i++) {
			tempPos[i].first = pos[3].first;
			tempPos[i].second = pos[3].second - i + 1;
		}
		for (int i = 2; i < 4; i++) {
			tempPos[i].first = pos[2].first;
			tempPos[i].second = pos[2].second - i + 2;
		}

		if (tempPos[3].second < 0) {
			move(tempPos, "right");
		}

	}
	// for 270 degrees rotation
	else if (rotation == 2) {

		for (int i = 0; i < 2; i++) {
			tempPos[i].first = pos[3].first - i + 1;
			tempPos[i].second = pos[3].second;
		}
		for (int i = 2; i < 4; i++) {
			tempPos[i].first = pos[2].first - i + 2;
			tempPos[i].second = pos[2].second;
		}

		if (tempPos[3].first < 0) {
			move(tempPos, "down");
		}

	}
	// for 360 degrees rotation
	else if (rotation == 3) {

		for (int i = 0; i < 2; i++) {
			tempPos[i].first = pos[3].first;
			tempPos[i].second = pos[3].second + i - 1;
		}
		for (int i = 2; i < 4; i++) {
			tempPos[i].first = pos[2].first;
			tempPos[i].second = pos[2].second + i - 2;
		}

		if (tempPos[3].second > cols - 1) {
			move(tempPos, "left");
		}

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

	// adding it onto the grid;
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