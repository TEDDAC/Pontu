#ifndef GAME_DRAWER_INCLUDED
#define GAME_DRAWER_INCLUDED

#include <SDL2/SDL.h>

#include "model/Game.h"
#include "engine/TextureHandler.h"
#include "engine/Button.h"


bool drawGame(SDL_Renderer* renderer, const SDL_Rect* windowSize, const SDL_Rect* boardRect, const Game* game,TextureHandler* textureHandler);

#endif
