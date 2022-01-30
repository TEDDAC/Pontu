#ifndef MENU_CONNECTION_INCLUDED
#define MENU_CONNECTION_INCLUDED

#include <SDL2/SDL.h>
#include <string.h>
#include "engine/Button.h"
#include "engine/TextLabel.h"
#include "engine/TextInput.h"
#include "engine/FontUtils.h"

bool drawMenuConnection(const SDL_Renderer* renderer, TTF_Font* font, int w, int h);

#endif
