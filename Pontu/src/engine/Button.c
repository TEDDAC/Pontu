#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>

P_Button createButton(SDL_Texture* texture, const int coordx,
				const int coordy, const int sizex, const int sizey,
				void (*onClick)(void))
{
	// Declarations
	P_Button b = { .rect = { .x = coordx, .y = coordy, .w = sizex, .h = sizey }, .onClick = onClick };

	assert(texture != NULL && "ERROR: Button created without texture");

	b.texture = texture;

	return b;
}

void drawButtonOnRenderer(SDL_Renderer* renderer,const P_Button* button)
{
	if(SDL_RenderCopy(renderer,button->texture,NULL,&(button->rect)))
	{
		fprintf(stderr,"Error: %s\n",SDL_GetError());
		exit(1);
	}
}

SDL_bool isHover(const P_Button button,const int x,const int y)
{
	SDL_Point coord;
	coord.x = x;
	coord.y = y;
	return SDL_PointInRect(&coord,&(button.rect));
}
