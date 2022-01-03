#include "debug/printer.h"
#include <stdio.h>

void printCoord(const Coord coord) {
	fprintf(stderr, "(%d, %d)", coord.x, coord.y);
}

