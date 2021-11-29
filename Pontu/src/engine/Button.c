#include <SDL2/sdl.h>
#include "../moteur/boutton.h"

/*
 * Return : 	a button within written <text>, placed in (<coordx>; <coordy>), sized <sizex>x<sizey>. The button returned will do <onClick> when it will be clicked
 *
 * Params : 	text	=> text written in the button
 * 		texture	=> background image for the button
 * 		coordx	=> placement in width
 *		coordy	=> placement in height
 *		sizex	=> button's width
 *		sizey	=> button's height
 *		onClick	=> Acction to do when the button is clicked
 *
 * Finality :	Create a brand new button with specs
*/
P_Button createButton(char* text, SDL_Texture* texture, int coorx, int coordy, int sizex, int sizey, void (*onClick)(void))
{
	// Declarations
	P_Button b;
	SDL_Rect rect;
	
	// Rect specs
	rect.x = coordx;
	rect.y = coordy;
	rect.w = sizex;
	rect.h = sizey;
	
	// Button specs
	b.text = text;
	b.onClick = onClick;
	b.rect = rect;

	return b;
}

