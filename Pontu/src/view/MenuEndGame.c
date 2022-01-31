#include "view/MenuEndGame.h"
#include <SDL2/SDL_ttf.h>
#include "engine/TextLabel.h"
#include <errno.h>
#include "engine/Colors.h"
#include "engine/InputProcessor.h"


void nullFunc(P_Button* caller) {

}

P_Button createButtonForEndGameMenu(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect* rect) {
	int sizeX;
	int sizeY;
	
	SDL_Texture* texture = createGenericButtonTexture("Retour menu", font, 50, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 1, 4, &sizeX, &sizeY, renderer);

	if (texture == NULL) {
		perror(SDL_GetError());
		exit(errno);
	}
	return createButton(texture, NULL, rect->x, rect->y, sizeX, sizeY, nullFunc);
}

void drawTitle(SDL_Renderer* renderer, const SDL_Rect* rect, FontHandler* fontHandler) {
	SDL_Point pos = {rect->x+rect->w/2, rect->y+rect->h/100};
	SDL_Color color = {0,0,0,0};

	TextLabel titre = createTextLabel("Scores", &pos, 4, &color, fontHandler->fonts[FONT_retro], renderer, POSX_CENTER, POSY_TOP);

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

void endGameMenu(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, FontHandler* fontHandler, const Player players[], const size_t nbPlayers) {
	InputProcessor inputProcessor = createInputProcessor();

	int windowW;
	int windowH;

	SDL_GetWindowSize(window, &windowW, &windowH);

	SDL_Rect rectMenuEndGame = {
		.x=windowW/10, 
		.y=0, 
		.w=windowW*80/100, 
		.h=windowH
	};
	

	array_P_Button_AddElement(&inputProcessor.tabButton, createButtonForEndGameMenu(renderer, fontHandler->fonts[FONT_retro], &rectMenuEndGame));
	P_Button* buttonMenuEndGame = array_P_Button_Last(&inputProcessor.tabButton);
	buttonMenuEndGame->rect.y = rectMenuEndGame.h*8/10;
	buttonMenuEndGame->rect.x = rectMenuEndGame.x + rectMenuEndGame.w/2-buttonMenuEndGame->rect.w/2;

	drawEndGameMenu(renderer, players, nbPlayers, &rectMenuEndGame, fontHandler);
	
	while(*generalState == GS_EndOfGameMenu)
	{
		{
			InputElement inputElement;
			while (InputType_None != (inputElement = proccessInput(&inputProcessor)).type) {

				switch (inputElement.type)
				{
				case InputType_ActivateUI:
					switch (inputElement.data.uiAction)
					{
					case UIAction_Quit:
						*generalState = GS_MainMenu;
						break;
					case UIAction_Validate:
						break;
					case UIAction_Cancel:
						break;
					default:
						break;
					}
					break;
				case InputType_MoveGame:
					
					break;
				case InputType_ClickGame:
					
					break;
				case InputType_None:
				default:
					break;
				}
			}
		}

		drawButtonOnRenderer(renderer, buttonMenuEndGame);

		SDL_RenderPresent(renderer);
		SDL_Delay(50);
	}

	freeInputProcessor(&inputProcessor);
}
