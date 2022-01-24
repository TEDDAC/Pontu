#ifndef TEXT_LABEL_INCLUDED
#define TEXT_LABEL_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine/FontLoader.h"

typedef enum {
	POSX_LEFT,
	POSX_CENTER,
	POSX_RIGHT
} POSITIONX_TYPE;

typedef enum {
	POSY_TOP,
	POSY_CENTER,
	POSY_BOTTOM
} POSITIONY_TYPE;

typedef struct
{
	char* text;
	SDL_Rect textZone;
	SDL_Color color;
	SDL_Texture* texture;
}TextLabel;

TextLabel createTextLabel(const char text[], const SDL_Point* pos, const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer, const POSITIONX_TYPE posXType, const POSITIONY_TYPE posYType);
void freeTextLabel(TextLabel* label);

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label);

#endif //TEXT_LABEL_INCLUDED
