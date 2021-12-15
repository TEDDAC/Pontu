#include "model/Game.h"
#include "model/IslandOrBridge.h"
#include <assert.h>

Game newGame(const size_t nbPlayers, const char* pseudos[]) {
	Game g = {
		// In Placement phase, the last player initialized is the 1st to play
		.currentPlayerID = nbPlayers - 1,
		.nb_rounds = 0,
		.phase = PLACEMENT,
		.board = newBoard(nbPlayers)
	};
	
	// red, green, blue, yellow
	// TODO meilleures couleurs (?)
	SDL_Color colors[4] = {
		{255,0  ,0  ,255},
		{0  ,255,0  ,255},
		{0  ,0  ,255,255},
		{255,255,0  ,255}
	};

	for (size_t player_i = 0; player_i < nbPlayers; player_i++) {
		g.arrPlayers[player_i] = newPlayer(pseudos[player_i] ,colors[player_i]);
	}
	
	return g;
}

bool placePiece(Piece* p, const Island island, const Board* b) {
	if (isIslandEmpty(island, b->arrPieces, b->nbPieces)) {
		p->island = island;
		return true;
	}

	return false;
}

bool movePiece(Piece* p, const Island i, const Board* b)
{
	if (isIslandEmpty(i, b->arrPieces, b->nbPieces) 
			&& isPieceAdjacentToIsland(*p, i) 
			&& checkBridge(p->island, i, b)) {
		p->island = i;
		
		return true;
	} else return false;
}

bool isIslandEmpty(const Island island, const Piece arrPieces[], const size_t nbPieces) {
	assert(islandValid(island) && "Pass invalid island to isIslandEmpty");

	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (islandEqual(island, arrPieces[i].island)) {
			return false;
		}
	}
	
	return true;
}

bool isPieceAdjacentToIsland(const Piece p, const Island i)
{
	//Maybe turn this into an if (with message on stderr)
	assert(islandValid(i) && "Send invalid island to isPieceAdjacentToIsland");
	assert(islandValid(p.island) && "Send invalid piece island to isPieceAdjacentToIsland");


	if(p.island.x==i.x) //piece and island are on the same x axis
	{
		const int diff=p.island.y-i.y;
		return -1==diff || diff==1; //Island is adjacent if the difference is equal -1 or 1 on the y axis
	}
	else if (p.island.y==i.y) //piece and island are on the same y axe
	{
		const int diff=p.island.x-i.x;
		return -1==diff || diff==1; //Island is adjacent if the difference is equal to -1 or 1 on the x axis
	}

	return false;
}

bool checkBridge(const Island start, const Island target, const Board* board)
{
	//Maybe turn this into an if (with message on stderr)
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
	if (xdiff == 0 && abs(ydiff) == 1) {
		return board->vBridges[start.y+ydiff][start.x];
	}
	// Horizontal bridge
	else if (abs(xdiff) == 1 && ydiff == 0) {
		return board->hBridges[start.y][start.x+xdiff];
	}
	// Not a bridge
	else {
		return false;
	}
}


bool isPieceIsolated(const Piece* piece, const Board* board) {
	Island g = piece->island;
	g.x-=1;
	Island d = piece->island;
	g.x+=1;
	Island h = piece->island;
	g.y-=1;
	Island b = piece->island;
	g.y+=1;

	if (islandValid(g) && checkBridge(piece->island, g, board)) return false;
	if (islandValid(d) && checkBridge(piece->island, d, board)) return false;
	if (islandValid(h) && checkBridge(piece->island, h, board)) return false;
	if (islandValid(b) && checkBridge(piece->island, b, board)) return false;
	return true;
}


bool areAllPlayerPiecesStucked(const size_t idJ,  const Piece arrPieces[], const size_t nbPieces) {
	for (size_t i = 0; i<nbPieces; ++i) {
		if (arrPieces[i].idJ == idJ && !arrPieces[i].stuck) {
			return false;
		}
	}
	return true;
}


bool cliqueOnBoard(const Coord coord, Game* game) {
	const IslandOrBridge islandOrBridge = coordToEntity(coord);

	switch(game->phase)
	{
	case PLACEMENT:
		if (islandOrBridge.type==ISLAND) {
			//placePiece(,islandOrBridge.x);
		}
		break;
	case RM_BRIDGE:
		if (islandOrBridge.type == BRIDGE) {
			Bridge bridge = islandOrBridge.data.bridge;
			rmBridge(bridge,&game->board);
			Piece* piecePotentialyIsolated = getPieceFromIsland(game->board.arrPieces, game->board.nbPieces, bridge.islandA);
			if (piecePotentialyIsolated != NULL && isPieceIsolated(piecePotentialyIsolated, &game->board)) { //Check is a piece is isolated and then if the player is eliminated
				piecePotentialyIsolated->stuck=true;
				if (areAllPlayerPiecesStucked(piecePotentialyIsolated->idJ, game->board.arrPieces, game->board.nbPieces)) {
					game->arrPlayers[piecePotentialyIsolated->idJ].rank = game->nb_rounds;//TODO : See what we put in rank
				}
			}
			
			// To factorise
			piecePotentialyIsolated = getPieceFromIsland(game->board.arrPieces, game->board.nbPieces, bridge.islandB);
			if (piecePotentialyIsolated != NULL && isPieceIsolated(piecePotentialyIsolated, &game->board)) { //Check is a piece is isolated and then if the player is eliminated
				piecePotentialyIsolated->stuck=true;
				if (areAllPlayerPiecesStucked(piecePotentialyIsolated->idJ, game->board.arrPieces, game->board.nbPieces)) {
					game->arrPlayers[piecePotentialyIsolated->idJ].rank = game->nb_rounds;//See what we put in rank
				}
			}

			return true;
		}
			
		break;
	default:
		break;
	}

	return false;
}

Piece* getPieceFromIsland(Piece arrPieces[9], const size_t logicalSize, const Island island){
	for(size_t i=0; i<logicalSize;i++)
	{
		if(islandEqual(arrPieces[i].island,island))
		{
			return &arrPieces[i];
		}
	}
	return NULL;
}

bool moveOnBoard(const Coord start, const Coord end, Game* game) {
	const IslandOrBridge islandOrBridgeStart = coordToEntity(start);
	const IslandOrBridge islandOrBridgeEnd = coordToEntity(end);

	switch(game->phase)
	{
		case MOVE_PIECE:
			if(islandOrBridgeStart.type==ISLAND && islandOrBridgeEnd.type==ISLAND)
			{
				Piece *piece;
				size_t idCurrentPlayer = game->currentPlayerID;
				Island islandStart = islandOrBridgeStart.data.island;
				Island islandEnd = islandOrBridgeEnd.data.island;
				piece=getPieceFromIsland(game->board.arrPieces, game->board.nbPieces,islandStart);
				if(idCurrentPlayer==piece->idJ) //Check if the current player id is the same than the piece selected by the player
					return movePiece(piece, islandEnd, &game->board);
				return false;
			}
	}

	return false;
}

bool rmBridge(Bridge bridge, Board* board) {

		if(bridge.islandA.x==bridge.islandB.x) //Horizontal bridge
		{
			if(board->hBridges[bridge.islandA.y][bridge.islandA.x]) {
				board->hBridges[bridge.islandA.y][bridge.islandA.x] = false; //bridge coordinates equals to the islandA
				return true;
			}
		}
		else if(bridge.islandA.y==bridge.islandB.y){ //Vertical bridge 
			if(board->vBridges[bridge.islandA.y][bridge.islandA.x]) {
				board->vBridges[bridge.islandA.y][bridge.islandA.x] = false;
				return true;
			}
	}

	return false;

}

