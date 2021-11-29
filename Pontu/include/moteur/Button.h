#ifndef BUTTON_INCLUDED
#define BUTTON_INCLUDED

#include <SDL2/sdl.h>
#include <SDL2/SDL_ttf.h>
typedef struct {
    char *text;
    SDL_Texture texture; //sprite ou texture de fond
    SDL_Rect rect; //définie les coordonnées et la taile, pour la hitbox et l'affichage
} P_Button;

P_Button createButton(char* text, SDL_Texture* texture,TTF_Font* police, int coordx, int coordy, int sizex, int sizey);
// texture: design du bouton, si rien n'est passer, le bouton sera générer dans la fonction.

void putButtonOnRenderer(SDL_Renderer* renderer, P_Button* button);
#ifndef
