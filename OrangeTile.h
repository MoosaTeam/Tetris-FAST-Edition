#pragma once

#include "Block.h"

class OrangeTile : public Block {

public:

	// constructor
	OrangeTile();

	// functions
	void rotate(int**& grid, int rows, int cols) override;

};