#include "view/MenuEndGame.h"
#include <SDL2/SDL_ttf.h>
#include "engine/TextLabel.h"
#include <errno.h>
#include "engine/Colors.h"
#include "engine/InputProcessor.h"
#include "engine/UIElementUtils.h"
#include "engine/arrayTextLabel.h"
#include "engine/arrayPositionSpecifier.h"


struct endGameMenuTextLabel {
	struct array_TextLabel textLabels;
	struct array_PositionSpecifier positionSpecifiers;
};

/**
 * @brief Button handle which set a generalState to GS_MainMenu
 * 
 * @param caller The button clicked
 */
void setStateToMainMenu(P_Button* caller) {
	*((GeneralState*)caller->arg) = GS_MainMenu;
}

/**
 * @brief Create button For EndGameMenu
 * 
 * @param renderer The renderer where buttons will be drawn
 * @param font Font used by buttons
 * @param rect Rect in which the endGameMenu is drawn
 * @param state generalState which will be attached to the button 
 * @return P_Button 
 */
P_Button createButtonForEndGameMenu(SDL_Renderer* renderer, TTF_Font* font, const SDL_Rect* rect, GeneralState* state) {
	int sizeX;
	int sizeY;
	
	SDL_Texture* texture = createGenericButtonTexture("Retour menu", font, 50, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND, 4, 4, &sizeX, &sizeY, renderer);
	if (texture == NULL) {
		perror(SDL_GetError());
		exit(errno);
	}
	SDL_Texture* textureHover = createGenericButtonTexture("Retour menu", font, 50, COLOR_GENERIC_BUTTON_BORDER, COLOR_GENERIC_BUTTON_BACKGROUND_HOVER, 8, 4, &sizeX, &sizeY, renderer);
	if (textureHover == NULL) {
		perror(SDL_GetError());
		exit(errno);
	}
	

	P_Button buttonMenuEndGame = createButton(texture, textureHover, rect->x, rect->y, sizeX, sizeY, &setStateToMainMenu);
	buttonMenuEndGame.arg = state;
	buttonMenuEndGame.rect.y = rect->h*8/10;
	buttonMenuEndGame.rect.x = rect->x + rect->w/2-buttonMenuEndGame.rect.w/2;
	return buttonMenuEndGame;
}

/**
 * @brief Draw title for End Game 
 * 
 * @param renderer The renderer where title will be drawn
 * @param rect Rect in which the endGameMenu is drawn
 * @param font Font used for title
 */
void drawTitle(SDL_Renderer* renderer, const SDL_Rect* rect, TTF_Font* font) {

	/*drawTextLabel(renderer, &titre);

	freeTextLabel(&titre);*/
}

/**
 * @brief Draw Pseudo and rank for end game menu
 * 
 * @param renderer The renderer where pseudo and rank will be drawn
 * @param rect Rect in which the endGameMenu is drawn
 * @param height Height of line in score table
 * @param font Font used for pseudo and rank
 * @param color Color used for pseudo and rank
 * @param rank 
 * @param pseudo 
 */
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

void drawPlayersScores(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, TTF_Font* font) {
	SDL_Color black = {0,0,0,0};
	for (size_t i=0; i<nbPlayers; ++i) {
		const int height = rect->y+(players[i].rank+1)*rect->h/10+rect->y+rect->h/100;

		drawPseudoAndRank(renderer, rect, height, font, &black,  i, players[i].pseudo);
		
		drawEliminationTurn(renderer, rect, height, font, &black, players[i].eliminationTurn);
	}
}

void drawEndGameMenu(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const SDL_Rect* rect, FontHandler* fontHandler) {
    
    SDL_SetRenderDrawColor(renderer, 220,220,220,255);
    SDL_RenderFillRect(renderer, rect);

	drawTitle(renderer, rect, fontHandler->fonts[FONT_retro]);
    
    drawPlayersScores(renderer, players, nbPlayers, rect, fontHandler->fonts[FONT_retro]);
}

TextLabel createTitleLabel(SDL_Renderer* renderer, TTF_Font* font) {
	SDL_Color color = {0,0,0,0};

	return createUnsizedTextLabel("Scores", &color, font, renderer);
}

PositionSpecifier getTitleRect100(SDL_Rect* labelSize) {
	SDL_Rect base100 = {
		.x=50,
		.y=1,
		.w = 30,
		.h = 30*labelSize->h/labelSize->w
	};
	return newPositionSpecifier(&base100, POSX_CENTER, POSY_TOP, ASPECT_KEEP_W);
}

struct endGameMenuTextLabel createLabels(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, FontHandler* fontHandler) {
	struct endGameMenuTextLabel labels = {
		.textLabels = array_TextLabel_Create(),
		.positionSpecifiers = array_PositionSpecifier_Create()
	};

	// Titre
	array_TextLabel_AddElement(&labels.textLabels, createTitleLabel(renderer, fontHandler->fonts[FONT_retro]));
	array_PositionSpecifier_AddElement(&labels.positionSpecifiers, getTitleRect100(&array_TextLabel_Last(&labels.textLabels)->textZone));



	return labels;
}

void endGameMenu(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, FontHandler* fontHandler, const Player players[], const size_t nbPlayers) {
	int windowW;
	int windowH;

	SDL_GetWindowSize(window, &windowW, &windowH);

	SDL_Rect rectMenuEndGame = {
		.x=windowW/10, 
		.y=0, 
		.w=windowW*80/100, 
		.h=windowH
	};
	
	InputProcessor inputProcessor = createInputProcessor();
	array_P_Button_AddElement(&inputProcessor.tabButton, createButtonForEndGameMenu(renderer, fontHandler->fonts[FONT_retro], &rectMenuEndGame, generalState));
	P_Button* buttonMenuEndGame = array_P_Button_Last(&inputProcessor.tabButton);
	SDL_Rect base100 = {
		.x = 50,
		.y = 99,
		.w = 30,
		.h = 30*buttonMenuEndGame->rect.h/buttonMenuEndGame->rect.w
	};
	drawEndGameMenu(renderer, players, nbPlayers, &rectMenuEndGame, fontHandler);
	
	struct endGameMenuTextLabel labels =  createLabels(renderer, players, nbPlayers, fontHandler);
	for (size_t i=0; i<labels.textLabels.size; ++i) {
		labels.textLabels.elems[i].textZone = adaptPosToRect(&labels.positionSpecifiers.elems[i], &rectMenuEndGame);
		drawTextLabel(renderer, &labels.textLabels.elems[i]);
	}

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
						*generalState = GS_Quit;
						break;
					case UIAction_Validate:
						break;
					case UIAction_Cancel:
						break;
					default:
						break;
					}
					break;
				case InputType_Window_Resize: {
					
					SDL_Rect rectM = {
						.x=inputElement.data.windowSize.w/10, 
						.y=0, 
						.w=inputElement.data.windowSize.w*80/100, 
						.h=inputElement.data.windowSize.h
					};
					drawEndGameMenu(renderer, players, nbPlayers, &rectM, fontHandler);
					
					for (size_t i=0; i<labels.textLabels.size; ++i) {
						labels.textLabels.elems[i].textZone = adaptPosToRect(&labels.positionSpecifiers.elems[i], &rectM);
						drawTextLabel(renderer, &labels.textLabels.elems[i]);
					}

					//buttonMenuEndGame->rect = adaptPosToRect(&base100, &rectM, POSX_CENTER, POSY_BOTTOM, ASPECT_KEEP_W);
					fprintf(stderr, "Resize\n"); fflush(stderr);
				} 
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
