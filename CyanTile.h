#pragma once

#include "Block.h"

class CyanTile : public Block {

public:

	// constructor
	CyanTile();

	// functions
	void rotate(int**& grid, int rows, int cols) override;

};

