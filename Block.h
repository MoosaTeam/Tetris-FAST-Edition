#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Block {

protected:

	// variables
	int rotation = 0;
	void move(pair<int, int>*& POS, string dir);

public:

	// destructor
	~Block();

	// positions of a full block
	pair<int, int>* pos;

	// functions
	bool find(pair<int, int> point);
	virtual void rotate(int**& grid, int rows, int cols) = 0;
	void moveBlock(int**& grid, int rows, int cols, string dir);
	

};