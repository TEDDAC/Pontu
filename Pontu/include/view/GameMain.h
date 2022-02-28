#ifndef GAME_MAIN_INCLUDED
#define GAME_MAIN_INCLUDED

#include "engine/GeneralState.h"
#include <SDL2/SDL.h>
#include "model/Player.h"
#include "engine/FontLoader.h"
#include "engine/AudioHandler.h"

void gameView(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, Player players[], size_t nbPlayers, FontHandler* fontHandler, AudioHandler audioHandler);

#endif //GAME_MAIN_INCLUDED
