#pragma once

#include "Block.h"

class GreenTile : public Block {

public:

	// constructor
	GreenTile();

	// functions
	void rotate(int**& grid, int rows, int cols) override;

};