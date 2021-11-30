#include "model/Piece.h"

Piece newPiece(const int idJ) {
	Piece piece = { 
		.idJ = idJ,
		.stuck = false
	} ;
	return piece;
}

