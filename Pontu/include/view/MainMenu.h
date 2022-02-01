#ifndef MAIN_MENU_INCLUDED
#define MAIN_MENU_INCLUDED

#include <SDL2/SDL.h>
#include <string.h>
#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/FontLoader.h"
#include "engine/GeneralState.h"

P_Button* drawMainMenu(SDL_Renderer* renderer,const FontHandler fontHandler, unsigned int* nb, const SDL_Rect* windowSize);

int mainMenu(SDL_Renderer * renderer,SDL_Window * window, GeneralState * generalState,FontHandler fontHandler);

#endif
