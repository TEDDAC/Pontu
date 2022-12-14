/**
 * \file Board.h
 * \brief Board management
 * \author Théotime Maillarbaux
 * \date 29/11/221
 */

#ifndef BOARD_H
#define BOARD_H

#include <stdbool.h>
#include <stddef.h>
#include "model/Piece.h"
#include <SDL2/SDL_pixels.h> // SDL_Color

/**
 * \struct Board
 * \brief Represents a board for a Game.
 *
 * The bridges are represented by 2D-arrays of bools.
 * For a given set of coordinates, the value is TRUE if the bridge is there,
 * else false.
 */
typedef struct {
	//            y  x
	bool vBridges[4][5]; ///< 2D-array of vertical bridges.
	bool hBridges[5][4]; ///< 2D-array of horizontal bridges.
	Piece arrPieces[9]; ///< Array of pieces on the Board.
	const size_t nbPieces; ///< Logical size of arrPieces
} Board;

/**
 * \brief Create a new board 
 * 
 * \param nbPlayers The number of players
 * \return A new board for nbPlayers
 */
Board newBoard(const size_t nbPlayers);

#endif // BOARD_H
