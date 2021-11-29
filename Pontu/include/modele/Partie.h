/**
 * \file Partie.h
 * \brief Gestion de la partie
 * \author Théotime Maillarbaux
 * \date 29/11/2021
 */

#ifndef PARTIE_H
#define PARTIE_H

#include "model/Player.h"
#include "model/Board.h"


/**
 * \enum Etat
 * \brief Représente l'état de la partie en cours
 */
typedef enum {
	PLACEMENT,
	GAME
} State;

/**
 * \struct Game
 * \brief Represents a game
 */
typedef struct {
	int currentPlayerID; ///< The ID of the one currently playing
	int nb_rounds; ///< The number of rounds so far
	//TODO duree
	State state; ///< The current state of the game
	Player arrPlayers[4]; ///< The array of all the players in this game
	Board board; ///< The board for this game
} Game;

/**
 * \brief Makes a new Game
 * \param[in]	nbPlayers	The number of players for this game
 * \return A struct representing the game
 */
Game newGame(int nbPlayers);

#endif //PARTIE_H
