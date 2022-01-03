#include "engine/TextureLoader.h"
#include <string.h>
#include <stdio.h>
#include <SDL2/SDL.h>

SDL_Texture* createTextureFromPath(SDL_Renderer* renderer, char* path)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* picture = IMG_Load(path);
	if(picture == NULL)
	{
		fprintf(stderr, "WARNNING: %s\n", SDL_GetError());
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, picture);
	SDL_FreeSurface(picture);
	if(texture == NULL)
	{
		fprintf(stderr, "WARNNING: %s\n", SDL_GetError());
		return NULL;
	}
	return texture;
}

SDL_Texture* createGenericButtonTexture(char* text, TTF_Font* font, int* sizex, int* sizey, SDL_bool forHover)
{
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC38

	SDL_Color background = { 85, 39, 163, 255};
	SDL_Color outline = { 134, 64, 255, 255};
	int thickness = 1; //thickness of the outline;

	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;

	//rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
		exit(1);
    }

    if(0 != SDL_SetRenderDrawColor(renderer, 0,0,0,0))  //choisi la couleur avec laquelle travailler
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
        exit(1);
    }
}
