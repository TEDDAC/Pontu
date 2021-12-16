#include "model/Coord.h"

Coord newCoord(const int x, const int y) {
	Coord c = {.x = x, .y = y};
	return c;
}

bool coordValid(const Coord coord)
{
	return coord.x >= 0 && coord.y >= 0 
		&& coord.x < 9 && coord.y < 9;
}

bool coordEqual(const Coord a, const Coord b)
{
	return a.x == b.x && a.y == b.y;
}
