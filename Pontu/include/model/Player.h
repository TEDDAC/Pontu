/**
 * \file Player.h
 * \brief Represents a player
 * \author Théotime Maillarbaux
 * \date 29/11/2021
 */

#ifndef PLAYER_H
#define PLAYER_H

#define PSEUDO_LENMAX 13

#include "model/PlayersColors.h"
#include <string.h>


/**
 * \struct Player
 * \brief Player during a game
 */
typedef struct {
	char pseudo[PSEUDO_LENMAX]; //< The player's pseudo
	PlayersColors color; //< The player's Piece' color
	int rank; //< The player's rank (1 if the player isn't out yet)
	int eliminationTurn; //< When the player has been eliminated (0 if the player isn't out yet)
} Player;

/**
 * \brief Creates a new Player
 * \param[in]	pseudo	The new Player's pseudo
 * \param[in]	color	The color of the new Player's Piece
 * \return A struct representing the new Player
 */
Player newPlayer(const char pseudo[PSEUDO_LENMAX], const PlayersColors color);


#endif // JOUEUR_H
