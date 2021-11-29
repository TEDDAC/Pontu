#include "engine/Button.h"
#include <stdio.h>
#include <assert.h>

/*
 * Return : 	a button within written <text>, placed in (<coordx>; <coordy>), sized
 *<sizex>x<sizey>. The button returned will do <onClick> when it will be clicked If text and texture
 *are not define, the function will return NULL and an error is printed in STDERR.
 *
 * Params :	texture	=> background image for the button (can be NULL)
 * 		coordx	=> placement in width
 *		coordy	=> placement in height
 *		sizex	=> button's width
 *		sizey	=> button's height
 *		onClick	=> Acction to do when the button is clicked
 *
 * Finality :	Create a brand new button with specs
 */
P_Button createButton(SDL_Texture* texture, int coordx, int coordy, int sizex, int sizey, void (*onClick)(void))
{
	// Declarations
	P_Button b = { .rect = { .x = coordx, .y = coordy, .w = sizex, .h = sizey }, .onClick = onClick };

	assert(texture != NULL && "WARNING: Button created without texture");

	return b;
}

SDL_bool putButtonOnRenderer(SDL_Renderer* renderer, TTF_Font* police, P_Button* button) {}
