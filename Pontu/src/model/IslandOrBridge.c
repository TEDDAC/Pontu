#include "model/IslandOrBridge.h"

IslandOrBridge coordToEntity(const Coord c) {
	if (c.x % 2 == 0) { // even columns
		if (c.y % 2 == 0) { // Island
			
			IslandOrBridge res = {
							.type = ISLAND, 
							.data.island = {.x=c.x/2, .y=c.y/2}
			};
			
			return res;
		} 
		else { // c.y % 2 != 0
			// Vertical bridge

			IslandOrBridge res = {
				.type = BRIDGE,
				.data.bridge = {
					.islandA= {.x = c.x/2, .y = (c.y - 1)/2},
					.islandB= {.x = c.x/2, .y = 1+(c.y - 1)/2}
				}
			};

			return res;
		}
	}
	else { // c.x % 2 != 0
		if (c.y % 2 == 0) {
			// Horizontal bridge
			IslandOrBridge res = {
				.type = BRIDGE,
				.data.bridge = {
					.islandA = {.x = (c.x-1)/2, .y = c.y/2},
					.islandB = {.x = 1+(c.x-1)/2, .y = c.y/2}
				}
			};

			return res;
		} 
		else { // c.y % 2 != 0
			IslandOrBridge res = {
				.type = WATER
			};
			return res;
		}
	}
}

