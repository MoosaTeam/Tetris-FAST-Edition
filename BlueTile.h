#pragma once

#include "Block.h"

class BlueTile : public Block {

public:

	// constructor
	BlueTile();

	// functions
	void rotate(int**& grid, int rows, int cols) override;

};

