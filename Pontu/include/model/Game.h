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
#include "model/Bridge.h"
#include "model/Island.h"
#include "model/Coord.h"
#include <SDL2/SDL_pixels.h>
#include <stdbool.h> 

/**
 * \enum Phase
 * \brief Represents the phase of the current game
 */
typedef enum {
	PLACEMENT,
	MOVE_PIECE,
	RM_BRIDGE
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
 * \brief Place a piece into the board
 * 
 * \param [in, out] p The piece to place
 * \param [in] island The island where the piece is placed
 * \param [in] b The board in which the piece is placed
 * \return true If the pieces is placed
 */
bool placePiece(Piece* p, const Island island, const Board* b);

/**
 * \brief Move a piece to an island
 * \param[in,out]	p the piece to move
 * \param[in]		i island target
 * \param[in]		b The Board for this Game
 * \return True if the piece can be move otherwise false
 */
bool movePiece(Piece* p, const Island i, const Board* b);

/**
 * \brief Check if an island is empty 
 * 
 * \param [in] island The island to check
 * \param [in] arrPieces the array of piece from the board
 * \param [in] nbPieces number of pieces 
 * \return true if none of the pieces is on th island, false otherwise
 */
bool isIslandEmpty(const Island island, const Piece arrPieces[], const size_t nbPieces);

/**
 * \brief Check if the the island is adjacent to the piece
 * \param[in] p the piece
 * \param[in] i island target
 * \return True if the island is adjacent to the piece otherwise false
 */
bool isPieceAdjacentToIsland(const Piece p, const Island i);


/**
 * \bref Check if there is a bridge between two Island.
 * \param[in]	start	On island were the bridge ends
 * \param[in]	target	The other island were the bridge ends
 * \param[in]	b	The Board for this Game.
 * \return true if there is a bridge, false otherwise.
 */
bool checkBridge(const Island start, const Island target, const Board* b);

/**
 * \brief Remove bridge from board at (coord->x; coord->y)
 * \param[in]	coords	Bridge to remove
 * \param[in]	board	Actual game board
 * \return True on success. Else return false.
 */
bool rmBridge(Bridge bridge, Board* board);

#endif //GAME_H

