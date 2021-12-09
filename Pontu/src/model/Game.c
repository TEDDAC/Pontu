#include "model/Game.h"

Game newGame(const int nbPlayers, const char* pseudos[]) {
	Game g;
	// In Placement phase, the last player initialized is the 1st to play
	g.currentPlayerID = nbPlayers - 1;
	g.nb_rounds = 0;
	g.phase = PLACEMENT;
	g.board = newBoard(nbPlayers);
	
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


bool movePiece(Piece* p, Island* i, Board b)
{
	if (checkIsland(*p,*i) && checkBridge(p->island,*i,b)) {
		p->island.hasPiece = false;
		p->island = *i;
		i->hasPiece = true;
		
		return true;
	} else return false;
}

//Not yet over
bool checkIsland(Piece p, Island i)
{
	bool check;
	int diff;
	if(p.island.x==i.x) //piece and island are on the same x axis
	{
		diff=p.island.y-i.y;
		return -1<diff && diff<1 && !(i.hasPiece); //Island is atteinable if the difference is between -1 and 1 y on the y axis
			
	}
	else if (p.island.y==i.y) //piece and island are on the same y axe
	{
		diff=p.island.x-i.y;
		return -1<diff && diff<1 && !(i.hasPiece); //Island is atteinable if the difference is between -1 and 1 x on the x axis
	}

	return false;

}

bool checkBridge(Island start, Island target, Board b)
{
	// Horizontal movement to get to the target Island.
	// If xdiff is negative, then the Piece will move left.
	// If xdiff is positive, then the Piece will move right.
	// If xdiff is 0, then the Piece won't move horizontally.
	xdiff = target.x - start.x;
	// Vertical movement to get to the target Island.
	// Works similarly to xdiff, except negative and positive values
	// indicate that the Piece will move upwards and downwards respectively.
	ydiff = target.y - start.y;

	// Vertical move
	if (abs(xdiff) == 0 && abs(ydiff) == 1) {
		return board.vBridges[start.y+ydiff][start.x];
	}
	// Horizontal move
	else if (abs(xdiff) == 1 && abs(ydiff) == 0) {
		return board.hBridges[start.y][start.x+xdiff];
	}
	// Illegal move
	else {
		return false;
	}
}


