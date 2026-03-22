#include "YellowTile.h"

// construction
YellowTile::YellowTile() {

	pos = new pair<int, int>[4];

	// adding the initial position for the whole block
	for (int ind = 0, j = 4; j <= 5; ind++, j++) {
		pos[ind].first = 0;
		pos[ind].second = j;
	}

	for (int ind = 2, j = 4; j <= 5; ind++, j++) {
		pos[ind].first = 1;
		pos[ind].second = j;
	}

}

// just an empty function because yellow blocks cannot rotate
void YellowTile::rotate(int**& grid, int rows, int cols) {

}
