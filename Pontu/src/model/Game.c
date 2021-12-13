#include "model/Game.h"
#include "model/IslandOrBridge.h"
#include <assert.h>

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
<<<<<<< HEAD
		
		
		break;
=======
		/*if (islandOrBridge.type == )
			rmBridge
			if (isIslandIsolated()) {
				
			}
		break;*/
>>>>>>> cacb66ccf9c68400e71a998e9349c7dce919383f
	default:
		break;
	}
}

bool moveOnBoard(const Coord start, const Coord end, Game* game) {
	const IslandOrBridge islandOrBridge = coordToEntity(coord);

	switch(game->phase)
	{
		case 
	}
}

bool rmBridge(Bridge bridge, Board* board) {

		if(brige.islandA.x==bridge.islandB.x) //Horizontal bridge
		{
			if(board->hBridges[bridge.islandA.y][bridge.islandA.x])
				board->hBridges[bridge.islandA.y][bridge.islandA.x] = false; //Brige coordinates equals to the islandA
				return true;
		}

		else if(brige.islandA.y==bridge.islandB.y){ //Vertical bridge 
			if(board->vBridges[bridge.islandA.y][bridge.islandA.x]) {
				board->vBridges[bridge.islandA.y][bridge.islandA.x] = false;
				return true;
			}
	}

	return false;

}

