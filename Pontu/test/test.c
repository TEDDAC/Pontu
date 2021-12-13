#include "model/Game.h"
#include "model/IslandOrBridge.h"
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


void testCoordToEntity() {
	for (int iX = 0; iX < 9; iX+=2)
	{
		for (int iY = 0; iY < 9; iY+=2)
		{
			Coord c = {.x = iX, .y = iY};
			Island i = {.x = iX/2, .y= iY/2};
			assert(coordToEntity(c).type==ISLAND);
			assert(islandEqual(i, coordToEntity(c).data.island));
		}	
	}

	for (int wX = 1; wX < 9; wX+=2)
	{
		for (int wY = 1; wY < 9; wY+=2)
		{
			Coord c = {.x = wX, .y = wY};
			assert(coordToEntity(c).type==WATER);
		}	
	}

	for (int bX = 0; bX < 9; bX+=2)
	{
		for (int bY = 1; bY < 9; bY+=2)
		{
			Coord c = {.x = bX, .y = bY};
			assert(coordToEntity(c).type==BRIDGE);
		}
	}

	for (int bX = 1; bX < 9; bX+=2)
	{
		for (int bY = 0; bY < 9; bY+=2)
		{
			Coord c = {.x = bX, .y = bY};
			assert(coordToEntity(c).type==BRIDGE);
		}
	}
}



int callAll() {
	testIsIslandEmpty();
	testIsPieceAdjacentToIsland();
	testPlacePiece();
	testCheckBridge();
	testCoordToEntity();

	return 0;
}


