#include "model/Board.h"

Board newBoard(const int nbPlayers) {
	const int nbPiecesPerPlayer = (nbPlayers == 4) ? 2 : 3;
	Board board = {.nbPieces = nbPiecesPerPlayer*nbPlayers};
	int pieceIndex = 0;

	// Init pieces for each player
	for (int player_i = 0; player_i < nbPlayers; player_i++) {
		for (int piece_i = 0; piece_i < nbPiecesPerPlayer; piece_i++) {
			board.arrPieces[pieceIndex] = newPiece(player_i);
			pieceIndex++;
		}
	}
	
	// Init bridges
	// max of vy (vertical y) is equal to max of hx (horizontal x),
	// so vy will be used as hx as well.
	for (int vy = 0; vy < 4; vy++) {
		for (int vx = 0; vx < 5; vx++) {
			board.vBridges[vy][vx] = true;
			board.hBridges[vx][vy] = true;
		}
	}
	return board;
}




