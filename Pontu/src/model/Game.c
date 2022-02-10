#include "model/Game.h"
#include "model/IslandOrBridge.h"
#include "engine/ArrayUtils.h"
#include <assert.h>

// Not defined in header to not pollute inferface
void applySpecificRulesFor2PlayersGame(Game* g)
{
	g->currentPlayerID = 0;
	g->phase		   = MOVE_PIECE;

	size_t iJ1 = 0;
	size_t iJ2 = 0;

	const Island startPosJ1[] = { newIsland(1, 0), newIsland(2, 1), newIsland(3, 0) };

	const Island startPosJ2[] = { newIsland(1, 4), newIsland(2, 3), newIsland(3, 4) };

	for (size_t i = 0; i < g->board.nbPieces; ++i)
	{
		if (g->board.arrPieces[i].idJ == 0)
		{
			g->board.arrPieces[i].island =
					startPosJ1[iJ1++]; // Post increment return the value "before" incrementing
		}
		else
		{
			g->board.arrPieces[i].island = startPosJ2[iJ2++];
		}
	}
}

Game newGame(const size_t nbPlayers, const Player player[])
{
	Game g = { // In Placement phase, the last player initialized is the 1st to play
		.currentPlayerID = nbPlayers - 1,
		.nb_rounds = 0,
		.phase = PLACEMENT,
		.board = newBoard(nbPlayers),
		.nbPlayers = nbPlayers,
		.lastRank = 0
	};

	for (size_t player_i = 0; player_i < nbPlayers; player_i++)
	{
		g.arrPlayers[player_i].color = player[player_i].color;
		g.arrPlayers[player_i].eliminationTurn = player[player_i].eliminationTurn;
		g.arrPlayers[player_i].rank = player[player_i].rank;
		strcpy(g.arrPlayers[player_i].pseudo, player[player_i].pseudo);
	}

	if (nbPlayers == 2)
	{
		applySpecificRulesFor2PlayersGame(&g);
	}

	return g;
}

void eliminatePlayer(Game* game, const size_t playerId) {
	game->arrPlayers[playerId].eliminationTurn = game->nb_rounds;
	++game->lastRank;
	game->arrPlayers[playerId].rank = game->lastRank;
	fprintf(stderr, "Rank : %d\n", game->lastRank);
}

void endGame(Game* game) {
	game->phase = GAME_ENDED;
}

void changePhaseOrPlayerTurn(Game* game)
{
	switch (game->phase)
	{
		case PLACEMENT:
			if (game->currentPlayerID == 0)
			{
				game->phase = MOVE_PIECE;
			}
			else
			{
				game->currentPlayerID--;
			}
			break;
		case MOVE_PIECE:
			game->phase = RM_BRIDGE;
			break;
		case RM_BRIDGE:
		{
			const size_t lastPlayerId = game->currentPlayerID;
			if (areAllPlayerPiecesStucked(lastPlayerId, game->board.arrPieces, game->board.nbPieces)) {
				eliminatePlayer(game, lastPlayerId);
				if (game->nbPlayers-1 == game->lastRank) {
					endGame(game);
					return;
				}
			}

			do
			{
				game->currentPlayerID++;
				if (game->currentPlayerID == game->nbPlayers)
				{
					game->currentPlayerID = 0;
				}
				/*if (lastPlayerId == game->currentPlayerID) {
					game->phase = GAME_ENDED;
					return;
				}*/

				if (game->arrPlayers[game->currentPlayerID].rank != 0 && areAllPlayerPiecesStucked(game->currentPlayerID, game->board.arrPieces, game->board.nbPieces)) {
					eliminatePlayer(game, game->currentPlayerID);
					if (game->nbPlayers-1 == game->lastRank) {
						endGame(game);
						return;
					}
				}

			} while (game->arrPlayers[game->currentPlayerID].rank != 0);


			fflush(stderr);

			if (anyOfPlayersPiecesCanMove(game->currentPlayerID, &game->board))
			{
				game->phase = MOVE_PIECE;
			}
			break;
		}
		default:
			break;
	}
}

bool placePiece(Piece* p, const Island island, const Board* b)
{
	if (isIslandEmpty(island, b->arrPieces, b->nbPieces))
	{
		p->island = island;
		return true;
	}

	return false;
}

bool movePiece(Piece* p, const Island i, const Board* b)
{
	if (pieceCanMoveTo(p, i, b))
	{
		p->island = i;
		return true;
	}
	else
	{
		return false;
	}
}

bool pieceCanMoveTo(const Piece* p, const Island i, const Board* b) {
	return isIslandEmpty(i, b->arrPieces, b->nbPieces) && isPieceAdjacentToIsland(*p, i) &&	checkBridge(p->island, i, b);
}

bool isIslandEmpty(const Island island, const Piece arrPieces[], const size_t nbPieces)
{
	assert(islandValid(island) && "Pass invalid island to isIslandEmpty");

	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (islandEqual(island, arrPieces[i].island))
		{
			return false;
		}
	}

	return true;
}

bool isPieceAdjacentToIsland(const Piece p, const Island i)
{
	// Maybe turn this into an if (with message on stderr)
	assert(islandValid(i) && "Send invalid island to isPieceAdjacentToIsland");
	assert(islandValid(p.island) && "Send invalid piece island to isPieceAdjacentToIsland");


	if (p.island.x == i.x) // piece and island are on the same x axis
	{
		const int diff = p.island.y - i.y;
		return -1 == diff || diff == 1; // Island is adjacent if the difference is equal -1 or 1 on the y axis
	}
	else if (p.island.y == i.y) // piece and island are on the same y axe
	{
		const int diff = p.island.x - i.x;
		return -1 == diff || diff == 1; // Island is adjacent if the difference is equal to -1 or 1 on the x axis
	}

	return false;
}

bool checkBridge(const Island start, const Island target, const Board* board)
{
	// Maybe turn this into an if (with message on stderr)
	assert(islandValid(start) && islandValid(target) && "Send invalid island to checkBridge");

	// Horizontal difference between start and target.
	// If xdiff is negative, then target is on the left of start.
	// If xdiff is positive, then target is on the right of start.
	// If xdiff is 0, then target and start are aligned horizontally.
	const int xdiff = target.x - start.x;
	// Vertical difference between start and target.
	// Works similarly to xdiff, except negative and positive values
	// indicate that target is above start and bellow start respectively.
	const int ydiff = target.y - start.y;

	// Vertical bridge
	if (xdiff == 0 && abs(ydiff) == 1)
	{
		const int coordY = start.y - (ydiff==-1?1:0);
		return board->vBridges[coordY][start.x];
	}
	// Horizontal bridge
	else if (abs(xdiff) == 1 && ydiff == 0)
	{
		const int coordX = start.x - (xdiff==-1?1:0);
		return board->hBridges[start.y][coordX];
	}
	// Not a bridge
	else
	{
		return false;
	}
}


bool isPieceIsolated(const Piece* piece, const Board* board)
{
	size_t nbNeighbors;
	Island* neighbors = islandsAround(piece->island, &nbNeighbors);

	for (size_t i = 0; i < nbNeighbors; ++i)
	{
		if (checkBridge(piece->island, neighbors[i], board)) {
			free(neighbors);
			return false;
		}
	}

	free(neighbors);
	return true;
}


bool areAllPlayerPiecesStucked(const size_t idJ, const Piece arrPieces[], const size_t nbPieces)
{
	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (arrPieces[i].idJ == idJ && !arrPieces[i].stuck)
		{
			return false;
		}
	}
	return true;
}

bool anyOfPlayersPiecesCanMove(const size_t playerID, const Board* board) {
	for (size_t i = 0; i < board->nbPieces; ++i)
	{
		size_t nbNeighbors;
		Island* neighbors = islandsAround(board->arrPieces[i].island, &nbNeighbors);
		for (size_t n = 0; n < nbNeighbors; ++n)
		{
			if (board->arrPieces[i].idJ == playerID && pieceCanMoveTo(&board->arrPieces[i], neighbors[n], board)) {
				return true;
			}
		}
		free(neighbors);
	}
	return false;
}

/*
	I think we shouldn't put this in the header (not intended to be used by exterior)

	It's used when a bridge is removed
*/
void updatePieceIsolated(Game* game, const Island* island)
{
	Piece* piecePotentialyIsolated = getPieceFromIsland(game->board.arrPieces, game->board.nbPieces, *island);
	if (piecePotentialyIsolated != NULL && isPieceIsolated(piecePotentialyIsolated, &game->board))
	{ // Check is a piece is isolated and then if the player is eliminated
		piecePotentialyIsolated->stuck = true;
		if (areAllPlayerPiecesStucked(piecePotentialyIsolated->idJ, game->board.arrPieces,
									  game->board.nbPieces))
		{
			game->arrPlayers[piecePotentialyIsolated->idJ].rank = game->nb_rounds; // TODO : See what we put in rank
		}
	}
}

GameAction clickOnBoard(const Coord coord, Game* game)
{
	const IslandOrBridge islandOrBridge = coordToEntity(coord);

	switch (game->phase)
	{
		case PLACEMENT:
			if (islandOrBridge.type == ISLAND)
			{
				Piece* piece = getPieceFromIsland(game->board.arrPieces, game->board.nbPieces, islandOrBridge.data.island);
				if (piece != NULL) {
					if (placePiece(piece, islandOrBridge.data.island, &game->board)) {
						changePhaseOrPlayerTurn(game);
						return GameAction_PlacePiece;
					}
				}
			}
			break;
		case RM_BRIDGE:
			if (islandOrBridge.type == BRIDGE)
			{
				Bridge bridge = islandOrBridge.data.bridge;
				if (rmBridge(bridge, &game->board)) {
					updatePieceIsolated(game, &bridge.islandA);
					updatePieceIsolated(game, &bridge.islandB);

					changePhaseOrPlayerTurn(game);

					return GameAction_RemoveBridge;
				}
			}
			break;
		default:
			break;
	}

	return GameAction_None;
}

Piece* getPieceFromIsland(Piece arrPieces[9], const size_t logicalSize, const Island island)
{
	for (size_t i = 0; i < logicalSize; i++)
	{
		if (islandEqual(arrPieces[i].island, island))
		{
			return &arrPieces[i];
		}
	}
	return NULL;
}

GameAction moveOnBoard(const Coord start, const Coord end, Game* game)
{
	const IslandOrBridge islandOrBridgeStart = coordToEntity(start);
	const IslandOrBridge islandOrBridgeEnd	 = coordToEntity(end);

	switch (game->phase)
	{
		case MOVE_PIECE:
			if (islandOrBridgeStart.type == ISLAND && islandOrBridgeEnd.type == ISLAND)
			{
				const size_t idCurrentPlayer = game->currentPlayerID;
				const Island islandStart	 = islandOrBridgeStart.data.island;
				const Island islandEnd		 = islandOrBridgeEnd.data.island;
				Piece* piece = getPieceFromIsland(game->board.arrPieces, game->board.nbPieces, islandStart);
				if (piece != NULL && idCurrentPlayer == piece->idJ)
				{ // Check if the current player id is the same than the piece selected by the player
					bool pieceMoved = movePiece(piece, islandEnd, &game->board);
					if (pieceMoved)
					{
						changePhaseOrPlayerTurn(game);
					}
					return pieceMoved ? GameAction_MovePiece : GameAction_None;
				}
			}
			break;
		default:
			break;
	}

	return GameAction_None;
}

bool rmBridge(Bridge bridge, Board* board)
{

	if (bridge.islandA.x == bridge.islandB.x) // Vertical bridge
	{
		if (board->vBridges[bridge.islandA.y][bridge.islandA.x])
		{
			board->vBridges[bridge.islandA.y][bridge.islandA.x] = false;
			return true;
		}
	}
	else if (bridge.islandA.y == bridge.islandB.y)
	{ // Horizontal bridge
		if (board->hBridges[bridge.islandA.y][bridge.islandA.x])
		{
			board->hBridges[bridge.islandA.y][bridge.islandA.x] = false; // bridge coordinates equals to the islandA
			return true;
		}
	}

	return false;
}


struct array_Coord getInteractiveCases(const Game* const game, const Coord selectedCase) {
	switch (game->phase)
	{
	case PLACEMENT: {
		struct array_Coord retVal = array_Coord_Create();
		array_Coord_Reserve(&retVal, 25);

		for (int y = 0; y<5; y+=2) {
			for (int x = 0; x<5; x+=2) {
				array_Coord_AddElement(&retVal, newCoord(x,y));
			}
		}

		for (size_t i = 0; i < game->board.nbPieces; i++)
		{
			if (islandValid(game->board.arrPieces[i].island)) {
				array_Coord_RemoveElement(&retVal, islandToCoord(&game->board.arrPieces[i].island), &coordEqual);
			}
		}

		array_Coord_FitToSize(&retVal);

		return retVal;
	}
	case MOVE_PIECE: {
		struct array_Coord retVal = array_Coord_Create();
		array_Coord_Reserve(&retVal, 4);

		for (size_t i = 0; i < game->board.nbPieces; ++i)
		{
			if (game->board.arrPieces[i].idJ == game->currentPlayerID && !game->board.arrPieces[i].stuck) {
				size_t nbIsland;
				Island* islands = islandsAround(game->board.arrPieces[i].island, &nbIsland);

				if (nbIsland != 0) {
					Coord pieceCoord = islandToCoord(&game->board.arrPieces[i].island);
					if (!coordValid(selectedCase)) {
						array_Coord_AddElement(&retVal, pieceCoord);
					}
					else {
						if (coordEqual(pieceCoord, selectedCase)) {
							for (size_t iIsle = 0; iIsle < nbIsland; ++iIsle)
							{
								if (pieceCanMoveTo(&game->board.arrPieces[i], islands[iIsle], &game->board)) {
									Coord coordIsland = islandToCoord(&islands[iIsle]);
									array_Coord_AddElement(&retVal, coordIsland);
								}
							}
							free(islands);
							return retVal;
						}
					}
				}
				free(islands);
			}
		}

		array_Coord_FitToSize(&retVal);
		return retVal;
	}
	case RM_BRIDGE: {
		struct array_Coord retVal = array_Coord_Create();
		array_Coord_Reserve(&retVal, 40);

		for (size_t y = 0; y<5; ++y) {
			for (size_t x = 0; x<4; ++x) {
				if (game->board.hBridges[y][x]) {
					Coord coord = {.x=x*2+1, .y=y*2};
					array_Coord_AddElement(&retVal, coord);
				}
			}
		}
		for (size_t y = 0; y<4; ++y) {
			for (size_t x = 0; x<5; ++x) {
				if (game->board.vBridges[y][x]) {
					Coord coord = {.x=x*2, .y=y*2+1};
					array_Coord_AddElement(&retVal, coord);
				}
			}
		}

		return retVal;
	}
	default:
		return array_Coord_Create();
	}
}
