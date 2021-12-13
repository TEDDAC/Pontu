#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

P_Button createButton(SDL_Texture* texture, SDL_Texture* hoverTexture ,const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(P_ButtonArg* arg))
{
	// Declarations
	P_Button b = { .rect = { .x = coordx, .y = coordy, .w = sizex, .h = sizey }, .onClick = onClick, .drawn = false};

	assert(texture != NULL && "ERROR: Button created without texture");

	b.texture = texture;
	b.hoverTexture = hoverTexture;
	return b;
}

bool drawButtonOnRenderer(SDL_Renderer* renderer, P_Button* button)
{
	if(SDL_RenderCopy(renderer,button->hover && button->hoverTexture != NULL ? button->hoverTexture : button->texture,NULL,&(button->rect)))
	{
		fprintf(stderr,"Warning: %s\n",SDL_GetError());
		return false;
	}
	button->drawn = true;
}

bool isHover(P_Button* button,const int x,const int y)
{
	SDL_Point coord;
	coord.x = x;
	coord.y = y;
	button->hover = SDL_PointInRect(&coord,&(button->rect));
	return button->hover && button->drawn;
}

bool changeButtonTexture(P_Button* button, SDL_Texture* texture)
{
	if(texture == NULL){
		fprintf(stderr,"Warning: button texture cannot change to NULL\n");
		return false;
	}
	button->texture = texture;
}
