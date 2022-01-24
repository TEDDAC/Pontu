#ifndef MENU_FIN_INCLUDED
#define MENU_FIN_INCLUDED

#include <SDL2/SDL.h>
#include "model/Player.h"
#include "engine/FontLoader.h"

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler);

#endif // MENU_FIN_INCLUDED
