#include "model/Game.h"

Game newGame(int nbPlayers) {
	Game g;
	// In Placement phase, the last player initialized is the 1st to play
	g.currentPlayerID = nbPlayers - 1;
	g.nb_rounds = 0;
	g.state = PLACEMENT;
	// TODO newBoard
	// TODO initPlayers (avec gestion des couleurs)
	return g;
}

