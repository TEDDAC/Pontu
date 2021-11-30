/**
 *\file Piece.h
 *\brief Piece's model       
 *\author Jacques
 *\date 29/11/2021 
 */

#ifndef PIECE_H
#define PIECE_H
#include "Island.h"
//#include "Player.h" //If we use a pointer for the player instead of an int 
#include <stdbool.h>

/**
 *\Struct Piece
 *\brief Piece representation 
 *\ Piece characteristics 
 */
typedef struct 
{
	int idJ; ///< Player's id (owner of the piece)
	bool stuck; ///< Evaluate to true if the piece is isolated
	Island island; ///< Piece's localisation on the game board
}Piece;

/**
 * \brief Creates a new Piece
 * \param[in]	idJ	The ID (index in array) of the Player owning the Piece
 */
Piece newPiece(const int idJ);

#endif // PIECE_H
