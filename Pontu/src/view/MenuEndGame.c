#include "view/MenuEndGame.h"
#include <SDL2/SDL_ttf.h>
#include "engine/TextLabel.h"

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler) {
    
    SDL_SetRenderDrawColor(renderer, 220,220,220,255);
    SDL_RenderFillRect(renderer, rect);

    { // Titre
        SDL_Point pos = {rect->x+rect->w/2, rect->y+rect->h/100};
        SDL_Color color = {0,0,0,0};

        TextLabel titre = createTextLabel("Scores", &pos, &color, fontHandler->fonts[FONT_retro], renderer, POSX_CENTER, POSY_TOP);

        drawTextLabel(renderer, &titre);

        freeTextLabel(&titre);
    }
    
    {// Joueurs
        char* text;
        for (size_t i=0; i<nbPlayers; ++i) {
            SDL_Point pos = {rect->x+rect->w*0.05, rect->y+(players[i].rank+1)*rect->h/10+rect->y+rect->h/100};
            SDL_Color color = {0,0,0,0};

            text = (char*) realloc(text, sizeof(char)*(4+strlen(players[i].pseudo)));// potentialy one character wider than necesarry
            sprintf(text, "%ld. %s", i, players[i].pseudo);

            TextLabel joueur = createTextLabel(text, &pos, &color, fontHandler->fonts[FONT_retro], renderer, POSX_LEFT, POSY_TOP);

            drawTextLabel(renderer, &joueur);

            freeTextLabel(&joueur);

            pos.x = rect->x+rect->w*0.95;
            text = (char*) realloc(text, sizeof(char*) * 10);
            sprintf(text, "Tour: %d", players[i].eliminationTurn);
            joueur = createTextLabel(text, &pos, &color, fontHandler->fonts[FONT_retro], renderer, POSX_RIGHT, POSY_TOP);
            drawTextLabel(renderer, &joueur);
            freeTextLabel(&joueur);
        }
        free(text);
    }
}

