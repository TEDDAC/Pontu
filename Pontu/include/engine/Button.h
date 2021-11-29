#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <SDL2/SDL_ttf.h>
#include <SDL2/sdl.h>
typedef struct
{
	SDL_Texture* texture; // sprite ou texture de fond
	SDL_Rect rect;		  // définie les coordonnées et la taile, pour la hitbox et l'affichage
	void (*onClick)(void);
} P_Button;

P_Button createButton(SDL_Texture* texture, int coordx, int coordy, int sizex, int sizey, void (*onClick)(void));
// texture: design du bouton, si rien n'est passer, le bouton sera générer dans la fonction.

SDL_bool putButtonOnRenderer(SDL_Renderer* renderer, TTF_Font* police, P_Button* button);

#endif
