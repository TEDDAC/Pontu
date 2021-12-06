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

bool movePiece(Piece p, Island i)
{
	return checkIsland(p,i) && checkBridge(p,i); //Otherwise call one function before one other
}

//Not yet over
bool checkIsland(Piece p, Island i)
{
	bool check;
	int diff;
	if(p.island.x==i.x) //piece and island are on the same x axe
	{
		diff=p.island.y-i.y;
		return -1<diff && diff<1; //Island is atteinable if the difference is between -1 and 1 y on the y axe 
			
	}
	else if (p.island.y==i.y) //piece and island are on the same y axe
	{
		diff=p.island.x-i.y;
		return -1<diff && diff<1; //Island is atteinable if the difference is between -1 and 1 x on the x axe 
	}

	return false;

}
