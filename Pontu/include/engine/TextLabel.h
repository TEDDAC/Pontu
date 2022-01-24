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

TextLabel createTextLabel(const char text[], const SDL_Point* pos, const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer);
void freeTextLabel(TextLabel* label);

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label);

#endif //TEXT_LABEL_INCLUDED
