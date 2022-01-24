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

SDL_Texture* createGenericButtonTexture(char* text, TTF_Font* font, int size, SDL_Color border_color, SDL_Color background_color, int thickness, int padding,int* sizex, int* sizey, SDL_Renderer* renderer)
{
	// https://www.libsdl.org/projects/SDL_ttf/docs/SDL_ttf.html#SEC38

    if(renderer == NULL)
    {
        fprintf(stderr, "Erreur createGenericButtonTexture: %s\n", "Le renderer ne peux pas être NULL");
		return NULL;
    }

    if(0 != SDL_SetRenderDrawColor(renderer, 0,0,0,0))  //choisi la couleur avec laquelle travailler
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
        return NULL;
    }

	if(font == NULL){
		fprintf(stderr, "Erreur: la police d'écriture ne peut pas être null à la création d'une texture.\n");
		return NULL;
	}

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, text, border_color);

    // now you can convert it into a texture
    SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int minx,maxx,miny,maxy,advance;
    if(TTF_GlyphMetrics(font,text,&minx,&maxx,&miny,&maxy,&advance)==-1){
	        printf("%s\n",TTF_GetError());
	}
    /*else {
        printf("minx    : %d\n",minx);
        printf("maxx    : %d\n",maxx);
        printf("miny    : %d\n",miny);
        printf("maxy    : %d\n",maxy);
        printf("advance    : %d\n",advance);
    }*/

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = padding+thickness+minx;  //controls the rect's x coordinate
    Message_rect.y = padding+thickness; // controls the rect's y coordinte
    Message_rect.w = strlen(text)*size*2/3; // controls the width of the rect
    Message_rect.h = size; // controls the height of the rect

	//pour les contour d'abord
	SDL_Rect button_rect;
	button_rect.x = 0;
	button_rect.y = 0;
	button_rect.w = Message_rect.w+2*(padding+thickness)+minx;
	button_rect.h = Message_rect.h+2*(padding+thickness);
	SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,button_rect.w,button_rect.h);
	SDL_SetRenderDrawColor(renderer, border_color.r,border_color.g,border_color.b,0);
    SDL_SetRenderTarget(renderer, texture);
	SDL_RenderFillRect(renderer, &button_rect);

	*sizex = button_rect.w;
	*sizey = button_rect.h;

	//pour le background
	button_rect.x = thickness;
	button_rect.y = thickness;
	button_rect.w = Message_rect.w+2*padding+minx;
	button_rect.h = Message_rect.h+2*padding;
	SDL_SetRenderDrawColor(renderer, background_color.r,background_color.g,background_color.b,0);
	SDL_RenderFillRect(renderer, &button_rect);

	SDL_SetRenderDrawColor(renderer, border_color.r,border_color.g,border_color.b,0);
    SDL_RenderCopy(renderer, message, NULL, &Message_rect);
	return texture;
}
