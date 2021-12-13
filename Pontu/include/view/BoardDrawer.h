#ifndef BOARD_DRAWER_INCLUDED
#define BOARD_DRAWER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

bool drawBoard(Renderer* renderer, const SDL_Rect* boardRect, SDL_Texture* island, SDL_Texture* bridge);


#endif
