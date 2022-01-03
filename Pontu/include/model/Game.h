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
#include "model/arrayCoord.h"
#include <SDL2/SDL_pixels.h>
#include <stdbool.h> 

/**
 * \enum Phase
 * \brief Represents the phase of the current game
 */
typedef enum {
	PLACEMENT,
	MOVE_PIECE,
	RM_BRIDGE,
	GAME_ENDED
} Phase;

/**
 * \struct Game
 * \brief Represents a game
 */
typedef struct {
	size_t currentPlayerID; ///< The ID of the one currently playing
	int nb_rounds; ///< The number of rounds so far
	//TODO duree
	Phase phase; ///< The current state of the game
	Player arrPlayers[4]; ///< The array of all the players in this game
	size_t nbPlayers; 
	Board board; ///< The board for this game
} Game;

/**
 * \brief Makes a new Game
 * \param[in]	nbPlayers	The number of players for this game
 * \return A struct representing the game
 */
Game newGame(const size_t nbPlayers, const char* pseudos[]);


/**
 * \brief (Should not be called outside Game.c) Used to change phase or player (or both) after an action
 * 
 * \param [in, out] game The game to mutate
 */
void changePhaseOrPlayerTurn(Game* game);

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
 * \brief Test if a movement is possible for a piece to a destination island
 * 
 * \param p The piece to test
 * \param i The destination island 
 * \param b The board
 * \return true if the piece p can move to the island i 
 */
bool pieceCanMoveTo(const Piece* p, const Island i, const Board* b);

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
 * \brief test if a piece is isolated
 * 
 * \param [in] piece The piece which is checked 
 * \param [in] board The board were the piece is
 * \return true if no bridge go from piece's island to another island, false otherwise
 */
bool isPieceIsolated(const Piece* piece, const Board* board);

/**
 * \brief test if all pieces from a player are stucked 
 * 
 * \param idJ Player id
 * \param arrPieces All pieces from board
 * \param nbPieces Number of pieces
 * \return true if all player's pieces are stucked, false otherwise
 */
bool areAllPlayerPiecesStucked(const size_t idJ,  const Piece arrPieces[], const size_t nbPieces);

/**
 * \brief Test if one piece of a player can move
 * 
 * \param playerID The player to check
 * \param board The board
 * \return true if at least one of player's piece can move 
 */
bool anyOfPlayersPiecesCanMove(const size_t playerID, const Board* board);

/**
 * \brief Check if there is a bridge between two Island.
 * \param[in]	start	On island were the bridge ends
 * \param[in]	target	The other island were the bridge ends
 * \param[in]	b	The Board for this Game.
 * \return true if there is a bridge, false otherwise.
 */
bool checkBridge(const Island start, const Island target, const Board* b);

/**
 * \brief Get piece from island
 * \param[in] arrPieces Array of all pieces
 * \param[in] logicalSize The logical size of arrPieces
 * \param[in] island The island on the one we want to check the piece
 * \return the piece address if there is one the island otherwise return NULL
 */
Piece* getPieceFromIsland(Piece arrPieces[9], const size_t logicalSize, const Island island);


/**
 * \brief  Handle global game action move
 * 
 * \param start Board coord were the move started
 * \param end Board coord were the move ended
 * \param game Game's state
 * \return true if an action was realised, false otherwise
 */
bool moveOnBoard(const Coord start, const Coord end, Game* game);

/**
 * \brief Handle global game action click
 * 
 * \param [in] coord Board coord were the click is
 * \param [in, out] game Game's state
 * \return true if an action was realised, false otherwise
 */
bool clickOnBoard(const Coord coord, Game* game);

/**
 * \brief Remove bridge from board at (coord->x; coord->y)
 * \param[in]	coords	Bridge to remove
 * \param[in]	board	Actual game board
 * \return True on success. Else return false.
 */
bool rmBridge(Bridge bridge, Board* board);

/**
 * \brief List cases that can be interacted with for movement
 * 
 * \param[in] game The game
 * \param[in] selectedCase The selected case
 * \return struct array_Coord An array of coord /!\ Care to free this array with array_Coord_Free
 */
struct array_Coord getInteractiveCases(const Game* const game, const Coord selectedCase);

#endif //GAME_H

