#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>

/*
 * Return : 	a button within written <text>, placed in (<coordx>; <coordy>), sized <sizex>x<sizey>. The button returned will do <onClick> when it will be clicked
 * 		If texture is not define, the function will return NULL and an error is printed in STDERR.
 *
 * Params :	texture	=> image for the button
 * 		coordx	=> placement in width
 *		coordy	=> placement in height
 *		sizex	=> button's width
 *		sizey	=> button's height
 *		onClick	=> Acction to do when the button is clicked
 *
 * Finality :	Create a brand new button with specs
*/
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

SDL_bool isHover(const P_Button button,const int x,const int y)
{
	SDL_Point coord;
	coord.x = x;
	coord.y = y;
	return SDL_PointInRect(&coord,&(button.rect));
}
