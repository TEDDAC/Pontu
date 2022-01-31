#include "view/MenuEndGame.h"
#include <SDL2/SDL_ttf.h>
#include "engine/TextLabel.h"


P_Button createButtonForEndGameMenu(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect* rect) {
    const SDL_Color black = {0,0,0,0};
    const SDL_Color white = {255,255,255,255};
	int sizeX;
	int sizeY;
	SDL_Texture* texture = createGenericButtonTexture("Retour menu", font, 14, black, white, 1, 4, &sizeX, &sizeY, renderer);

	return createButton(texture, texture, rect->x, rect->y, sizeX, sizeY, NULL);
}

void drawTitle(SDL_Renderer* renderer, const SDL_Rect* rect, FontHandler* fontHandler) {
	SDL_Point pos = {rect->x+rect->w/2, rect->y+rect->h/100};
	SDL_Color color = {0,0,0,0};

	TextLabel titre = createTextLabel("Scores", &pos, 2, &color, fontHandler->fonts[FONT_retro], renderer, POSX_CENTER, POSY_TOP);

	drawTextLabel(renderer, &titre);

	freeTextLabel(&titre);
}

void drawPseudoAndRank(SDL_Renderer* renderer, const SDL_Rect* rect, const int height, TTF_Font* font, const SDL_Color* color, const size_t rank, const char *const pseudo) {
	const SDL_Point posRangPseudo = {
		.x = rect->x+rect->w*0.05, 
		.y = height
	};

	char *const text = (char*) malloc(sizeof(char)*(4+strlen(pseudo)));// potentialy one character wider than necesarry
	if (text == NULL) {
		fprintf(stderr,"allocation error\n");
		fflush(stderr);
		return;
	}
	sprintf(text, "%lld. %s", rank, pseudo);

	TextLabel joueur = createTextLabel(text, &posRangPseudo, 1, color, font, renderer, POSX_LEFT, POSY_TOP);
	free(text);

	drawTextLabel(renderer, &joueur);

	freeTextLabel(&joueur);
}

void drawEliminationTurn(SDL_Renderer* renderer, const SDL_Rect* rect, const int height, TTF_Font* font, const SDL_Color* color, const int eliminationTurn) {
	SDL_Point posTourElimination = {
		.x = rect->x+rect->w*0.95,
		.y = height
	};


	char *const text = (char*) malloc(sizeof(char*) * 10);
	if (text == NULL) {
		fprintf(stderr,"allocation error\n");
		fflush(stderr);
		return;
	}
	sprintf(text, "Tour: %d", eliminationTurn);

	TextLabel label = createTextLabel(text, &posTourElimination, 1, color, font, renderer, POSX_RIGHT, POSY_TOP);
	
	free(text);
	drawTextLabel(renderer, &label);
	
	freeTextLabel(&label);
	
}

void drawPlayersScores(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler) {
	SDL_Color black = {0,0,0,0};
	for (size_t i=0; i<nbPlayers; ++i) {
		const int height = rect->y+(players[i].rank+1)*rect->h/10+rect->y+rect->h/100;

		drawPseudoAndRank(renderer, rect, height, fontHandler->fonts[FONT_retro], &black,  i, players[i].pseudo);
		
		drawEliminationTurn(renderer, rect, height, fontHandler->fonts[FONT_retro], &black, players[i].eliminationTurn);
	}
}

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler) {
    
    SDL_SetRenderDrawColor(renderer, 220,220,220,255);
    SDL_RenderFillRect(renderer, rect);

	drawTitle(renderer, rect, fontHandler);
    
    drawPlayersScores(renderer, players, nbPlayers, rect, fontHandler);
}

