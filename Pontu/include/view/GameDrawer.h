#ifndef GAME_DRAWER_INCLUDED
#define GAME_DRAWER_INCLUDED

#include <SDL2/SDL.h>

#include "model/Game.h"
#include "engine/TextureHandler.h"
#include "view/BoardDrawer.h"
#include "engine/Button.h"


bool drawGame(SDL_Renderer* renderer, SDL_Rect* windowSize, SDL_Rect* boardRect, Game* game,TextureHandler* textureHandler);

#endif
