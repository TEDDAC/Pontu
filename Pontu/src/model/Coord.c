#include "model/Coord.h"


bool coordValide(const Coord coord)
{
	return coord.x >= 0 && coord.y >= 0;
}

bool coordEqual(const Coord a, const Coord b)
{
	return a.x == b.x && a.y == b.y;
}
