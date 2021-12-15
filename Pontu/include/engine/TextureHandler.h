#ifndef TEXTURE_HANDLER_INCLUDED
#define TEXTURE_HANDLER_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include "engine/TextureLoader.h"

#define MACRO_FOR_ALL_TEXTURES(M) 	\
	M(Island)                     	\
	M(Bridge)                     	\
	M(Piece)						\
	M(Water)

#define MACRO_IDENTITY_COMMA(E) TEXTURE_##E,

typedef enum
{
	MACRO_FOR_ALL_TEXTURES(MACRO_IDENTITY_COMMA) 
	NB_TEXTURES_DEFINED
} EnumTextures;


typedef struct
{
	SDL_Texture* textures[NB_TEXTURES_DEFINED];
} TextureHandler;

TextureHandler newTextureHandler(SDL_Renderer* renderer);

void freeTextureHandler(TextureHandler* textureHandler);

#endif // TEXTURE_HANDLER_INCLUDED