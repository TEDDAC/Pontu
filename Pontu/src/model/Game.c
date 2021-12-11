#include "model/Game.h"
#include "model/IslandOrBridge.h"

Game newGame(const int nbPlayers, const char* pseudos[]) {
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

	for (int player_i = 0; player_i < nbPlayers; player_i++) {
		g.arrPlayers[player_i] = newPlayer(pseudos[player_i] ,colors[player_i]);
	}
	
	return g;
}


bool movePiece(Piece* p, const Island i, const Board* b)
{
	if (isIslandEmpty(i, b->arrPieces, b->nbPieces) 
			&& checkPieceAdjacentToIsland(*p, i) 
			&& checkBridge(p->island, i, b)) {
		p->island = i;
		
		return true;
	} else return false;
}

bool isIslandEmpty(const Island island, const Piece arrPieces[], const size_t nbPieces) {
	for (size_t i = 0; i < nbPieces; ++i)
	{
		if (IslandEqual(island, arrPieces[i].island)) {
			return false;
		}
	}
	
	return true;
}

bool checkPieceAdjacentToIsland(const Piece p, const Island i)
{
	if(p.island.x==i.x) //piece and island are on the same x axis
	{
		const int diff=p.island.y-i.y;
		return -1<diff && diff<1; //Island is atteinable if the difference is between -1 and 1 y on the y axis
	}
	else if (p.island.y==i.y) //piece and island are on the same y axe
	{
		const int diff=p.island.x-i.y;
		return -1<diff && diff<1; //Island is atteinable if the difference is between -1 and 1 x on the x axis
	}

	return false;
}

bool checkBridge(const Island start, const Island target, const Board* board)
{
	// Horizontal movement to get to the target Island.
	// If xdiff is negative, then the Piece will move left.
	// If xdiff is positive, then the Piece will move right.
	// If xdiff is 0, then the Piece won't move horizontally.
	const int xdiff = target.x - start.x;
	// Vertical movement to get to the target Island.
	// Works similarly to xdiff, except negative and positive values
	// indicate that the Piece will move upwards and downwards respectively.
	const int ydiff = target.y - start.y;

	// Vertical move
	if (abs(xdiff) == 0 && abs(ydiff) == 1) {
		return board->vBridges[start.y+ydiff][start.x];
	}
	// Horizontal move
	else if (abs(xdiff) == 1 && abs(ydiff) == 0) {
		return board->hBridges[start.y][start.x+xdiff];
	}
	// Illegal move
	else {
		return false;
	}
}

bool rmBridge(Coord coord, Board* board) {
	IslandOrBridge bridge = coordToEntity(coord);

	if (bridge.type == HBRIDGE) {
		if (board->hBridges[bridge.y][bridge.x]) {
			board->hBridges[bridge.y][bridge.x] = false;
			return true;
		}
	} 
	else if (bridge.type == VBRIDGE) {
		if (board->vBridges[bridge.y][bridge.x]) {
			board->vBridges[bridge.y][bridge.x] = false;
			return true;
		}
	}
	return false;
}

