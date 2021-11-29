#include "model/Piece.h"

Piece newPiece(int idJ) {
	Piece piece;
	piece.idJ = idJ;
	piece.stuck = false;
	return piece;
}

