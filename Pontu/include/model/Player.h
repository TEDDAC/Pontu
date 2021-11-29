/**
 * \file Player.h
 * \brief Represents a player
 * \author Théotime Maillarbaux
 * \date 29/11/2021
 */

#ifndef PLAYER_H
#define PLAYER_H

#define PSEUDO_LENMAX 50

#include <SDL2/SDL_pixels.h>
#include <string.h>

/**
 * \struct Player
 * \brief Player during a game
 */
typedef struct {
	char pseudo[PSEUDO_LENMAX]; //< The player's pseudo
	SDL_Color color; //< The player's Piece' color
	int rank; //< The player's rank (0 if the player isn't out yet)
} Joueur;

/**
 * \brief Creates a new Player
 * \param[in]	pseudo	The new Player's pseudo
 * \param[in]	color	The color of the new Player's Piece
 * \return A struct representing the new Player
 */
Player newPlayer(char pseudo[PSEUDO_LENMAX], SDL_Color color);


#endif // JOUEUR_H
