#ifndef MENU_FIN_INCLUDED
#define MENU_FIN_INCLUDED

#include <SDL2/SDL.h>
#include "model/Player.h"
#include "engine/FontLoader.h"

#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/GeneralState.h"

P_Button createButtonForEndGameMenu(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect* rect);

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler);

void endGameMenu(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, FontHandler* fontHandler, const Player players[], const size_t nbPlayers);


#endif // MENU_FIN_INCLUDED
