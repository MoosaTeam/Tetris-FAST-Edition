#include "Block.h"

// destructor
Block::~Block() {

	delete[] pos;

}

// finds a point in the block's positions
bool Block::find(pair<int, int> point) {

	for (int i = 0; i < 4; i++) {
		if (point.first == pos[i].first && point.second == pos[i].second)
			return true;
	}
	return false;

}

// moves a block in the direction specified
void Block::move(pair<int, int>*& POS, string dir) {

	if (dir == "down") {
		for (int i = 0; i < 4; i++) {
			POS[i].first++;
		}
	}
	else if (dir == "right") {
		for (int i = 0; i < 4; i++) {
			POS[i].second++;
		}
	}
	else if (dir == "left") {
		for (int i = 0; i < 4; i++) {
			POS[i].second--;
		}
	}
	else if (dir == "up") {
		for (int i = 0; i < 4; i++) {
			POS[i].first--;
		}
	}

}

// for player movement of the block and checks to see if it doesnt go out of bounds
void Block::moveBlock(int**& grid, int rows, int cols, string dir) {

	pair<int, int>* tempPos = new pair<int, int>[4];

	
	if (dir == "right") {
		for (int i = 0; i < 4; i++) {
			int x = pos[i].first;
			int y = pos[i].second;
			if (y + 1 > cols - 1 || (!find({ x, y + 1 }) && grid[x][y + 1] != 0)) {
				delete[] tempPos;
				return;
			}
			else {
				tempPos[i].first = x;
				tempPos[i].second = y + 1;
			}
		}
	}
	else if (dir == "left") {
		for (int i = 0; i < 4; i++) {
			int x = pos[i].first;
			int y = pos[i].second;
			if (y - 1 < 0 || (!find({ x, y - 1 }) && grid[x][y - 1] != 0)) {
				delete[] tempPos;
				return;
			}
			else {
				tempPos[i].first = x;
				tempPos[i].second = y - 1;
			}
		}
	}

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

}