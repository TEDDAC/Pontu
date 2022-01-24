#include "engine/TextLabel.h"



TextLabel createTextLabel(const char text[], const SDL_Rect* rect, const SDL_Color* color) {
    TextLabel label = {
        .textZone = *rect,
        .color = *color,
        .texture = NULL
    };

    label.text = (char*) malloc(sizeof(char)*strlen(text));
    strcpy(label.text, text);

    return label;
}

void freeTextLabel(TextLabel* label) {
    free(label->text);
    label->text = NULL;

    if (label->texture != NULL) {
        SDL_DestroyTexture(label->texture);
    }
}

void drawTextLabel(SDL_Renderer* renderer, TextLabel* label, TTF_Font* font) {
    if (label->texture == NULL) {
        SDL_Surface* surface = TTF_RenderText_Solid(font, label->text, label->color);

        if(surface == NULL)
        {
            fprintf(stderr, "WARNING: Can't write on TextLabel\n");
            return;
        }
        label->texture = SDL_CreateTextureFromSurface(renderer, surface);
        if(label->texture == NULL)
        {
            fprintf(stderr, "WARNING: Can't create texture from surface: %s\n", SDL_GetError());
            return;
        }

        SDL_FreeSurface(surface);
    }
    
    SDL_RenderCopy(renderer, label->texture, NULL, &label->textZone);
}

