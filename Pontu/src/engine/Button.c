#include "../moteur/boutton.h"

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
P_Button* createButton(SDL_Texture* texture, int coorx, int coordy, int sizex, int sizey, void (*onClick)(void))
{
	// Declarations
	P_Button* b;
	SDL_Rect rect;

	if(texture == NULL)
	{
		fprintf(stderr,"WARNING: Button created without texture");
		return NULL;
	}
	
	// Rect specs
	rect.x = coordx;
	rect.y = coordy;
	rect.w = sizex;
	rect.h = sizey;
	
	// Button specs
	b->onClick = onClick;
	b->rect = rect;

	return b;
}
 
SDL_Bool putButtonOnRenderer(SDL_Renderer* renderer, TTF_Font* police, P_Button* button)
{
	return SDL_TRUE;
}

