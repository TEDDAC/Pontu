#include "engine/TextLabel.h"
#include "engine/FontUtils.h"
#include "engine/TextureLoader.h"


TextLabel createTextLabel(const char text[], const SDL_Point* pos, const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer, const POSITIONX_TYPE posXType, const POSITIONY_TYPE posYType) {
    TextLabel label = {
        .color = *color,
        .texture = NULL
    };


    label.text = (char*) malloc(sizeof(char)*strlen(text));
	if (label.text == NULL) {
		fprintf(stderr, "ERROR: allocation error (createTextLabel)\n");
		fflush(stderr);
	}
    strcpy(label.text, text);

    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, label.text, label.color);

        if(surface == NULL)
        {
            fprintf(stderr, "WARNING: Can't write on TextLabel\n");
			fflush(stderr);
        }
        label.texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(label.texture == NULL)
        {
            fprintf(stderr, "WARNING: Can't create texture from surface: %s\n", SDL_GetError());
			fflush(stderr);
        }

        SDL_FreeSurface(surface);
    }

    label.textZone.w = calculateStringPixelLenght(font, label.text);
    label.textZone.h = TTF_FontHeight(font);

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
	
	fprintf(stderr, "freeTextLabel begin\n");
	fflush(stderr);
	if (label->text != NULL){
		free(label->text);
		label->text = NULL;
	}
    
	fprintf(stderr, "textFreed\n");
	fflush(stderr);

    if (label->texture != NULL) {
        SDL_DestroyTexture(label->texture);
		label->texture = NULL;
		fprintf(stderr, "textureFreed\n");
		fflush(stderr);
    }
	fprintf(stderr, "freeTextLabel end\n");
	fflush(stderr);
}

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label) {
    SDL_RenderCopy(renderer, label->texture, NULL, &label->textZone);
}

