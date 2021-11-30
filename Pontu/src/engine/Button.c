#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>

P_Button createButton(const SDL_Texture* texture, const int coordx,
				const int coordy, const int sizex, const int sizey,
				void (*onClick)(void))
{
	// Declarations
	P_Button b = { .rect = { .x = coordx, .y = coordy, .w = sizex, .h = sizey }, .onClick = onClick };

	assert(texture != NULL && "WARNING: Button created without texture");

	return b;
}

//SDL_bool putButtonOnRenderer(SDL_Renderer* renderer, TTF_Font* police, P_Button* button) {}
