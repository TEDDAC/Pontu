#include "model/IslandOrBridge.h"

IslandOrBridge(Coord c) {
	IslandOrBridge res;

	if (c.x % 2 == 0) {
		if (c.y % 2 == 0) {
			// Island
			res.x = c.x/2;
			res.y = c.y/2;
			res.type = ISLAND;
		} else { // c.y % 2 != 0
			// Vertical bridge
			res.x = c.x/2;
			res.y = c.y - 1;
			res.type = VBRIDGE;
		}
	} else { // c.x % 2 != 0
		if (c.y % 2 == 0) {
			// Horizontal bridge
			res.x = c.x - 1;
			res.y = c.y / 2;
			res.type = HBRIDGE;
		} else { // c.y % 2 != 0
			// Nothing in particular
			res.type = WATER;
		}
	}

	return res;
}

