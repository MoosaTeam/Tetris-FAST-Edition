#pragma once

#include "Block.h"

class PurpleTile : public Block {

public:
	
	// constructor
	PurpleTile();

	// functions
	void rotate(int**& grid, int rows, int cols);

};