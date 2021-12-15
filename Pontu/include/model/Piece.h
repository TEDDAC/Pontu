/**
 *\file Piece.h
 *\brief Piece's model       
 *\author Jacques Thomas
 *\date 29/11/2021 
 */

#ifndef PIECE_H
#define PIECE_H
#include "Island.h"
//#include "Player.h" //If we use a pointer for the player instead of an int 
#include <stdbool.h>
#include <stddef.h>

/**
 *\Struct Piece
 *\brief Piece representation 
 *\ Piece characteristics 
 */
typedef struct 
{
	size_t idJ; ///< Player's id (owner of the piece)
	bool stuck; ///< Evaluate to true if the piece is isolated
	Island island; ///< Piece's localisation on the game board
}Piece;

/**
 * \brief Creates a new Piece
 * \param[in]	idJ	The ID (index in array) of the Player owning the Piece
 */
Piece newPiece(const size_t idJ);

#endif // PIECE_H
