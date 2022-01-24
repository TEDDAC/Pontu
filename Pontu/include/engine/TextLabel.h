#ifndef TEXT_LABEL_INCLUDED
#define TEXT_LABEL_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine/FontLoader.h"

typedef struct
{
	char* text;
	SDL_Rect textZone;
	SDL_Color color;
	SDL_Texture* texture;
}TextLabel;

TextLabel createTextLabel(const char text[], const SDL_Rect* rect, const SDL_Color* color);
void freeTextLabel(TextLabel* label);

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label, TTF_Font* fontHandler);

#endif //TEXT_LABEL_INCLUDED
