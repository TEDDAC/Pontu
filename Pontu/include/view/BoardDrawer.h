#ifndef BOARD_DRAWER_INCLUDED
#define BOARD_DRAWER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "model/Board.h"

bool drawBoard(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Board* board, SDL_Texture* island, SDL_Texture* bridge);


#endif
