/**
 * \file Coord.h
 * \brief Board coordinates
 * \author Théotime Maillarbaux
 * \date 06/12/2021
 */

#ifndef COORD_INCLUDED
#define COORD_INCLUDED

#include <stdbool.h>

typedef struct {
	int x; ///< Coordinate on the X-axis
	int y; ///< Coordinate on the Y-axis
} Coord;


bool coordValide(const Coord coord);
bool coordEqual(const Coord a, const Coord b);

#endif //COORD_INCLUDED
