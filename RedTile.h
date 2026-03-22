#pragma once

#include "Block.h"

class RedTile : public Block {

public:

	// Constructor
	RedTile();

	// Functions
	void rotate(int**& grid, int rows, int cols) override;

};