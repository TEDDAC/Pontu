/**
 * \file Coord.h
 * \brief Board coordinates
 * \author Théotime Maillarbaux
 * \date 06/12/2021
 */

#ifndef COORD_INCLUDED
#define COORD_INCLUDED

#include <stdbool.h>

/**
 * \struct Coord
 * \brief From (0,0) to (8,8), represent a global coordinates in a board
 */
typedef struct {
	int x; ///< Coordinate on the X-axis
	int y; ///< Coordinate on the Y-axis
} Coord;

/**
 * \brief Create a new Coord (x,y)
 * 
 * \param [in] x 
 * \param [in] y 
 * \return new Coord 
 */
Coord newCoord(const int x, const int y);

/**
 * \brief Test if a coord is valide (ie x and y between 0 and 8)
 * 
 * \param [in] coord The coord to test
 * \return true if coord is valid, false otherwise
 */
bool coordValid(const Coord coord);


/**
 * \brief test if two coord are equal
 * 
 * \param [in] a One coord
 * \param [in] b One other coord
 * \return true if (a.x==b.x and a.y==b.y), false otherwise
 */
bool coordEqual(const Coord a, const Coord b);

#endif //COORD_INCLUDED
