#include "model/Island.h"


bool islandEqual(const Island a, const Island b) {
	return a.x == b.x && a.y == b.y;
}

bool islandValid(const Island island) {
	return island.x>=0 && island.x<=4
		&& island.y>=0 && island.y<=4;
}
