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

/**
 * \brief Create a new island
 * 
 * \param [in] x X coordinate of the island
 * \param [in] y Y coordinate of the island
 * \return The newly created Island
*/
Island newIsland(const int x, const int y);

/**
 * \brief Check if two islands are equal
 * 
 * \param a An island
 * \param b An island
 * \return true if a and b are equal
 */
bool islandEqual(const Island a, const Island b);

/**
 * \brief Check if an island is in board bounds
 * 
 * \param island the island to check
 * \return true is the island is in board bounds
 */
bool islandValid(const Island island);

#endif 
