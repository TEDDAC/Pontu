/**
 *\file Island.h
 *\brief Island's model       
 *\author Jacques, Théotime Maillarbaux
 *\date 29/11/2021 
 */

#ifndef ISLAND_H
#define ISLAND_H

#include <stdbool.h>
#include "model/Board.h"

/**
 *\struct  Island
 *\brief Island representation 
 * Island Coordinate on the game board
 */ 
typedef struct
{
	int x;///< Coordinate : absciss
	int y;///< Coordinate : ordinate
	Piece p; ///< The piece currently on the Island
} Island;

/**
 * \brief Creates a new Island
 * \param[in]	x	Coordinate on the X axis
 * \param[in]	y	Coordinate on the Y axis
 * \return Created Island
 */
Island newIsland(int x, int y);

/**
 * \brief Checks for available Island around a given one
 * \param[in]	startIsland	The Island from which we want to look for Islands
 * \param[in]	board		The Board used for this Game
 * \param[out]	result		An array of available Island
 */
void availableIslands(Island startIsland, Board board, Island result[]);

#endif 
