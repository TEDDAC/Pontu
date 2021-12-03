#include "model/Island.h"

Island newIsland(int x, int y) {
	Island i;
	i.x = x;
	i.y = y;
	return i;
}

void availableIslands(Island startIsland, int nbPlayers, Board board, Island result[]) {
	Piece pieces[9];
	Islands busyIslands[];

	availablePieces(nbPlayers, board, pieces);

	for (int i = 0; i<nbPlayers; i++) {
		busyIslands[i] = pieces[i].island;
	}

	if (startIsland.x != 0) {
		// There may be a vertical bridge above
		if (board.vBridges[startIsland.y][startIsland.x-1] == true) {
			
