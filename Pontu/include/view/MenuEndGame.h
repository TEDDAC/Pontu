#ifndef MENU_FIN_INCLUDED
#define MENU_FIN_INCLUDED

#include <SDL2/SDL.h>
#include "model/Player.h"
#include "engine/FontLoader.h"

#include "engine/Button.h"
#include "engine/TextureLoader.h"

P_Button createButtonForEndGameMenu(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect* rect);

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler);

#endif // MENU_FIN_INCLUDED
