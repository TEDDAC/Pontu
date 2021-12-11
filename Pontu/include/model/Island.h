/**
 *\file Island.h
 *\brief Island's model       
 *\author Jacques Thomas
 *\date 29/11/2021 
 */

#ifndef ISLAND_H
#define ISLAND_H

#include <stdbool.h>

/**
 *\struct  Island
 *\brief Island representation 
 * Island Coordinate on the game board
 */ 
typedef struct
{
	int x;///< Coordinate : absciss
	int y;///< Coordinate : ordinate
	// bool hasPiece; ///< Indicates if there is a Piece on this Island
} Island;

bool IslandEqual(const Island a, const Island b);

#endif 
