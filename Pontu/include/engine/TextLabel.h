#ifndef TEXT_LABEL_INCLUDED
#define TEXT_LABEL_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "engine/FontLoader.h"
#include "engine/UIElementUtils.h"

typedef struct
{
	char* text; 
	SDL_Rect textZone;
	SDL_Color color;
	SDL_Texture* texture;
}TextLabel;

TextLabel createTextLabel(const char text[], const SDL_Point* pos, const float factorSize,const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer, const PositionX_Type posXType, const PositionY_Type posYType);
TextLabel createUnsizedTextLabel(const char text[], const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer);
void freeTextLabel(TextLabel* label);

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label);

void clearTextLabel(SDL_Renderer* renderer, const TextLabel* label, SDL_Color color);

void replaceTextAndTextureOfTextLabel(SDL_Renderer* renderer, TextLabel* label, TTF_Font* font, char* text, SDL_Color* bg);

void copyTextIntoTextLabel(TextLabel* label, const char text[]);
void attachTextureToTextLabel(SDL_Renderer* renderer, TextLabel* label, TTF_Font* font);

#endif //TEXT_LABEL_INCLUDED
