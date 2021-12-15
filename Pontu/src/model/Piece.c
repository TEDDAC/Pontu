#include "model/Piece.h"

Piece newPiece(const size_t idJ) {
	Piece piece = { 
		.idJ = idJ,
		.stuck = false,
		.island = {.x = -1, .y=-1}
	};
	return piece;
}

