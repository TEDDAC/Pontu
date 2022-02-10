#include "engine/TextLabel.h"
#include "engine/FontUtils.h"
#include "engine/TextureLoader.h"
#include <errno.h>

void attachTextureToTextLabel(SDL_Renderer* renderer, TextLabel* label, TTF_Font* font) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, label->text, label->color);

	if(surface == NULL)
	{
		fprintf(stderr, "WARNING: Can't write on TextLabel\n");
		fflush(stderr);
	}
	else {
		label->texture = SDL_CreateTextureFromSurface(renderer, surface);
		if(label->texture == NULL)
		{
			fprintf(stderr, "WARNING: Can't create texture from surface: %s\n", SDL_GetError());
			fflush(stderr);
		}
		SDL_FreeSurface(surface);
	}
}

void copyTextIntoTextLabel(TextLabel* label, const char text[]) {
	label->text = (char*) malloc(sizeof(char)*(strlen(text)+1));
	if (label->text == NULL) {
		fprintf(stderr, "ERROR: allocation error (createTextLabel)\n");
		fflush(stderr);
        exit(errno);
	}
    strcpy(label->text, text);
}

TextLabel createUnsizedTextLabel(const char text[], const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer) {
	TextLabel label = {
		.color = color,
		.texture = NULL
	};

	copyTextIntoTextLabel(&label, text);

	attachTextureToTextLabel(renderer, &label, font);

	label.textZone.x = 0;
	label.textZone.y = 0;
    label.textZone.w = calculateStringPixelLenght(font, label.text);
    label.textZone.h = TTF_FontHeight(font);

	return label;
}

TextLabel createTextLabel(const char text[], const SDL_Point* pos, const float factorSize, const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer, const PositionX_Type posXType, const PositionY_Type posYType) {
    TextLabel label = {
        .color = *color,
        .texture = NULL
    };

	copyTextIntoTextLabel(&label, text);

	attachTextureToTextLabel(renderer, &label, font);

    label.textZone.w = calculateStringPixelLenght(font, label.text)*factorSize;
    label.textZone.h = TTF_FontHeight(font)*factorSize;

    switch (posXType)
    {
    case POSX_LEFT:
        label.textZone.x = pos->x;    
        break;
    case POSX_CENTER:
        label.textZone.x = pos->x-label.textZone.w/2;
        break;
    case POSX_RIGHT:
        label.textZone.x = pos->x-label.textZone.w;
        break;
    default:
        break;
    }

    switch (posYType)
    {
    case POSY_TOP:
        label.textZone.y = pos->y;    
        break;
    case POSY_CENTER:
        label.textZone.y = pos->y-label.textZone.h/2;
        break;
    case POSY_BOTTOM:
        label.textZone.y = pos->y-label.textZone.h;
        break;
    default:
        break;
    }

    return label;
}

void freeTextLabel(TextLabel* label) {
	if (label == NULL) return;
	
	if (label->text != NULL){
		free(label->text);
		label->text = NULL;
	}

    if (label->texture != NULL) {
        SDL_DestroyTexture(label->texture);
		label->texture = NULL;
    }
}

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label) {
    SDL_RenderCopy(renderer, label->texture, NULL, &label->textZone);
}

