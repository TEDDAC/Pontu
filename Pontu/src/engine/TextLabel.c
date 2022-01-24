#include "engine/TextLabel.h"
#include "engine/FontUtils.h"
#include "engine/TextureLoader.h"


TextLabel createTextLabel(const char text[], const SDL_Point* pos, const SDL_Color* color, TTF_Font* font, SDL_Renderer* renderer) {
    TextLabel label = {
        .color = *color,
        .texture = NULL
    };

    label.text = (char*) malloc(sizeof(char)*strlen(text));
    strcpy(label.text, text);
    
    {
        SDL_Surface* surface = TTF_RenderText_Solid(font, label.text, label.color);

        if(surface == NULL)
        {
            fprintf(stderr, "WARNING: Can't write on TextLabel\n");
        }
        label.texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(label.texture == NULL)
        {
            fprintf(stderr, "WARNING: Can't create texture from surface: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(surface);
    }


    label.textZone.x = pos->x;
    label.textZone.y = pos->y;
    label.textZone.w = calculateStringPixelLenght(font, label.text);
    label.textZone.h = TTF_FontHeight(font);

    return label;
}

void freeTextLabel(TextLabel* label) {
    free(label->text);
    label->text = NULL;

    if (label->texture != NULL) {
        SDL_DestroyTexture(label->texture);
    }
}

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label) {
    SDL_RenderCopy(renderer, label->texture, NULL, &label->textZone);
}

