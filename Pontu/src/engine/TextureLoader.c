#include "engine/TextureLoader.h"
#include <string.h>
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
