#include "model/Island.h"
#include <stdlib.h>


Island newIsland(const int x, const int y) {
	Island i = {
		.x = x,
		.y = y
	};
	return i;
}

bool islandEqual(const Island a, const Island b) {
	return a.x == b.x && a.y == b.y;
}

bool islandValid(const Island island) {
	return island.x>=0 && island.x<=4
		&& island.y>=0 && island.y<=4;
}


Island* islandsAround(const Island island, size_t* nbIslandsFound) {
	*nbIslandsFound = 0;
	Island* neighbors = (Island*) malloc(sizeof(Island)*4);

	// Left
	Island i = island; 
	i.x -= 1;
	if (islandValid(i)) {
		neighbors[*nbIslandsFound] = i;
		(*nbIslandsFound)++;
	}

	// Right
	i = island;
	i.x += 1;
	if (islandValid(i)) {
		neighbors[*nbIslandsFound] = i;
		(*nbIslandsFound)++;
	}
	
	// Up
	i = island;
	i.y -= 1;
	if (islandValid(i)) {
		neighbors[*nbIslandsFound] = i;
		(*nbIslandsFound)++;
	}

	// Down
	i = island;
	i.y += 1;
	if (islandValid(i)) {
		neighbors[*nbIslandsFound] = i;
		(*nbIslandsFound)++;
	}

	return neighbors;
}
