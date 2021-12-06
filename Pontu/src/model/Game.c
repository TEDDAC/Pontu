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

bool checkBridge(Coord* coords, Board* board)
{
	if((coords->x%2 == 1) && (coords->y%2 == 0))
	{
		return board->hBridge[coord->y][coord->x];
	}
	if((coords->x%2 == 0) && (coords->y%2 == 1))
	{
		return board->vBridge[coord->y][coord->x];
	}
	return false;
}

