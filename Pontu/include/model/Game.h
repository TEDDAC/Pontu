/**
 * \file Game.h
 * \brief Management of a Game
 * \author Théotime Maillarbaux
 * \date 29/11/2021
 */

#ifndef GAME_H
#define GAME_H

#include "model/Player.h"
#include "model/Board.h"
#include <SDL2/SDL_pixels.h>
#include <stdbool.h>

/**
 * \enum Phase
 * \brief Represents the phase of the current game
 */
typedef enum {
	PLACEMENT,
	GAME
} Phase;

/**
 * \struct Game
 * \brief Represents a game
 */
typedef struct {
	int currentPlayerID; ///< The ID of the one currently playing
	int nb_rounds; ///< The number of rounds so far
	//TODO duree
	Phase phase; ///< The current state of the game
	Player arrPlayers[4]; ///< The array of all the players in this game
	Board board; ///< The board for this game
} Game;

/**
 * \brief Makes a new Game
 * \param[in]	nbPlayers	The number of players for this game
 * \return A struct representing the game
 */
Game newGame(const int nbPlayers, const char* pseudos[]);


/**
 * \biref Check if there is a bridge at (coord->x; coord->y)
 * \param[in]	coords	Coords to test
 * \param[in]	board	Actual game board
 * \return True if there is a bridge. Else return false.
 */
bool checkBridge(Coord* coords, Board* board);

/**
 * \brief Remove bridge from board at (coord->x; coord->y)
 * \param[in]	coords	Bridge's coords to remove
 * \param[in]	board	Actual game board
 * \return True on succsess. Else return false.
 */
bool rmBridge(Coord* coords, Board* board);

#endif //PARTIE_H
