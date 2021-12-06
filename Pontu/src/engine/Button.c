#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>

P_Button createButton(SDL_Texture* texture, const int coordx,
				const int coordy, const int sizex, const int sizey,
				void (*onClick)(void))
{
	// Declarations
	P_Button b = { .rect = { .x = coordx, .y = coordy, .w = sizex, .h = sizey }, .onClick = onClick };

	assert(texture != NULL && "WARNING: Button created without texture");

	b.texture = texture;

	return b;
}

SDL_bool drawButtonOnRenderer(SDL_Renderer* renderer,const P_Button* button)
{
	SDL_RenderCopy(renderer,button->texture,NULL,&(button->rect));
}
