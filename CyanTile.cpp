#include "CyanTile.h"

// constructor
CyanTile::CyanTile() {

	pos = new pair<int, int>[4];

	// defining the intial positions for the whole block
	for (int ind = 0, j = 3; j <= 6; ind++, j++) {
		pos[ind].first = 0;
		pos[ind].second = j;
	}


}

// function to rotate the block
void CyanTile::rotate(int**& grid, int rows, int cols) {

	pair<int, int>* tempPos = new pair<int, int>[4];

	// for 90 degrees rotation
	if (rotation == 0) {
		for (int i = 0; i < 4; i++) {
			tempPos[i].first = pos[2].first + i - 1;
			tempPos[i].second = pos[2].second;
		}
		if (tempPos[0].first < 0)
			move(tempPos, "down");
		
		if (tempPos[2].first > rows - 1) {
			move(tempPos, "up");
			move(tempPos, "up");
		}

		if (tempPos[3].first > rows - 1) {
			move(tempPos, "up");
		}

	}
	// for 180 degrees rotation
	else if (rotation == 1) {
		for (int i = 0; i < 4; i++) {
			tempPos[i].first = pos[2].first;
			tempPos[i].second = pos[2].second + 1 - i;
		}
		if (tempPos[0].second > cols - 1) {
			move(tempPos, "left");
		}
		
		if (tempPos[2].second < 0) {
			move(tempPos, "right");
			move(tempPos, "right");
		}

		if (tempPos[3].second < 0) {
			move(tempPos, "right");
		}

	}
	// for 270 degrees rotation
	else if (rotation == 2) {

		for (int i = 0; i < 4; i++) {
			tempPos[i].first = pos[2].first + 1 - i;
			tempPos[i].second = pos[2].second;
		}

		if (tempPos[0].first > rows - 1) {
			move(tempPos, "up");
		}
		
		if (tempPos[2].first < 0) {
			move(tempPos, "down");
			move(tempPos, "down");
		}

		if (tempPos[3].first < 0) {
			move(tempPos, "down");
		}

	}
	// for 360 degrees rotation
	else if (rotation == 3) {

		for (int i = 0; i < 4; i++) {
			tempPos[i].first = pos[2].first;
			tempPos[i].second = pos[2].second - 1 + i;
		}

		if (tempPos[0].second < 0)
			move(tempPos, "right");

		if (tempPos[2].second > cols - 1) {
			move(tempPos, "left");
			move(tempPos, "left");
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

	// adding it onto the grid
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


