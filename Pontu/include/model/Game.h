/**
 * \file Game.h
 * \brief Management of a Game
 * \author Théotime Maillarbaux, Jacques Thomas
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
 * \brief Move a piece to an island
 * \param[in] p the piece to move
 * \param[in] i island target
 * \return True if the piece can be move otherwise false
 */

bool movePiece(Piece p, Island i);


/**
 * \brief Check if the the island is attainable from the piece's position (no player on the island)
 * \param[in] p the piece to move
 * \param[in] i island target
 * \return True if the island is attainable (no player on the island) otherwise false
 */
bool checkIsland(Piece p, Island i);


#endif //PARTIE_H
