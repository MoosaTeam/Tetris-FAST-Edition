#pragma once

#include "Block.h"

class YellowTile : public Block {

public:

	// constructor
	YellowTile();

	// functions
	void rotate(int**& grid, int rows, int cols) override;

};