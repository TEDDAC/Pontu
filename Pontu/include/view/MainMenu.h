#ifndef MAIN_MENU_INCLUDED
#define MAIN_MENU_INCLUDED

#include <SDL2/SDL.h>
#include <string.h>
#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/FontLoader.h"
#include "engine/GeneralState.h"
#include "engine/AudioHandler.h"

P_Button* createMainMenu(SDL_Renderer* renderer,const FontHandler fontHandler, unsigned int* nb, const SDL_Rect* windowSize, GeneralState* generalState);

int mainMenu(SDL_Renderer * renderer,SDL_Window * window, GeneralState * generalState,FontHandler fontHandler, AudioHandler audioHandler);

#endif //MAIN_MENU_INCLUDED
