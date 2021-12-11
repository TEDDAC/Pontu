#include "model/Game.h"
#include <assert.h>

void testIsIslandEmpty() {
	Piece arrPieces[4] = {
		newPiece(0),
		newPiece(0),
		newPiece(1),
		newPiece(1),
	};
	
	Island i = {.x = 2, .y = 4};
	
	assert(isIslandEmpty(i, arrPieces, 4));

	arrPieces[1].island = i;
	assert(!isIslandEmpty(i, arrPieces, 4));
	arrPieces[1].island.x-=1;
	assert(isIslandEmpty(i, arrPieces, 4));
	arrPieces[3].island = i;
	assert(!isIslandEmpty(i, arrPieces, 4));
}

void testIsPieceAdjacentToIsland() {
	Piece piece = newPiece(0);
	Island i = {.x = 2, .y = 4};

	piece.island.x=0;
	piece.island.y=0;

	assert(!isPieceAdjacentToIsland(piece, i));

	piece.island = i;
	assert(!isPieceAdjacentToIsland(piece, i));

	piece.island.x-=1;
	assert(isPieceAdjacentToIsland(piece, i));

	piece.island.y-=1;
	assert(!isPieceAdjacentToIsland(piece, i));

	piece.island.x+=1;
	assert(isPieceAdjacentToIsland(piece, i));
}

void testPlacePiece() {
	Board board = newBoard(2);
	Island island = {.x = 0, .y = 0};

	assert(placePiece(&board.arrPieces[0], island, &board));
	assert(islandEqual(board.arrPieces[0].island, island));
	assert(!placePiece(&board.arrPieces[1], island, &board));
	assert(!islandEqual(board.arrPieces[1].island, island));
}

void testCheckBridge() {
	Board board = newBoard(2);

}

int main(int argc, char * argv[]) {
	testIsIslandEmpty();
	testIsPieceAdjacentToIsland();
	testPlacePiece();
	testCheckBridge();

	return 0;
}
