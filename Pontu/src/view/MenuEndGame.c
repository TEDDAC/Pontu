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

SDL_Rect getEndGameMenuRect(SDL_Window* window) {
	int windowW;
	int windowH;
	SDL_GetWindowSize(window, &windowW, &windowH);

	SDL_Rect rect = {
		.x=windowW/10, 
		.y=0, 
		.w=windowW*80/100, 
		.h=windowH
	};
	return rect;
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

TextLabel createTitleLabel(SDL_Renderer* renderer, TTF_Font* font) {
	SDL_Color color = {0,0,0,0};

	return createUnsizedTextLabel("Scores", &color, font, renderer);
}

TextLabel createEliminationTurnLabel(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color* color, const int eliminationTurn) {
	char *const text = (char*) malloc(sizeof(char*) * 10);
	if (text == NULL) {
		fprintf(stderr,"allocation error\n");
		fflush(stderr);
		return createUnsizedTextLabel("Error allocation", color, font, renderer);
	}
	sprintf(text, "Tour: %d", eliminationTurn);

	TextLabel label = createUnsizedTextLabel(text, color, font, renderer);
	
	free(text);

	return label;
}

TextLabel createPseudoAndRankLabel(SDL_Renderer* renderer, TTF_Font* font, const SDL_Color* color, const int rank, const char *const pseudo) {
	char *const text = (char*) malloc(sizeof(char)*(4+strlen(pseudo)));// potentialy one character wider than necesarry
	if (text == NULL) {
		fprintf(stderr,"allocation error\n");
		fflush(stderr);
		return createUnsizedTextLabel("Error allocation", color, font, renderer);
	}
	sprintf(text, "%d. %s", rank, pseudo);

	TextLabel pseudoRankLbl = createUnsizedTextLabel(text, color, font, renderer);
	free(text);

	return pseudoRankLbl;
}

PositionSpecifier getPseudoAndRankPositionSpecifier(const SDL_Rect* labelSize, const int rank) {
	SDL_Rect base100 = {
		.x=2,
		.y=20+8*(rank-1),
		.w = 5*labelSize->w/labelSize->h,
		.h = 5
	};
	return newPositionSpecifier(&base100, POSX_LEFT, POSY_TOP, ASPECT_KEEP_FIT);
}

PositionSpecifier getEliminationTurnPositionSpecifier(const SDL_Rect* labelSize, const int rank) {
	SDL_Rect base100 = {
		.x=98,
		.y=20+8*(rank-1),
		.w = 5*labelSize->w/labelSize->h,
		.h = 5
	};
	return newPositionSpecifier(&base100, POSX_RIGHT, POSY_TOP, ASPECT_KEEP_FIT);
}

PositionSpecifier getTitlePositionClassifier(const SDL_Rect* labelSize) {
	SDL_Rect base100 = {
		.x=50,
		.y=1,
		.w = 15*labelSize->w/labelSize->h,
		.h = 15
	};
	return newPositionSpecifier(&base100, POSX_CENTER, POSY_TOP, ASPECT_KEEP_FIT);
}

struct endGameMenuTextLabel createLabels(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, FontHandler* fontHandler) {
	struct endGameMenuTextLabel labels = {
		.textLabels = array_TextLabel_Create(),
		.positionSpecifiers = array_PositionSpecifier_Create()
	};

	// Titre
	array_TextLabel_AddElement(&labels.textLabels, createTitleLabel(renderer, fontHandler->fonts[FONT_retro]));
	array_PositionSpecifier_AddElement(&labels.positionSpecifiers, getTitlePositionClassifier(&array_TextLabel_Last(&labels.textLabels)->textZone));

	// Lignes de score
	for (size_t i=0; i<nbPlayers; ++i) {
		array_TextLabel_AddElement(&labels.textLabels, createPseudoAndRankLabel(renderer, fontHandler->fonts[FONT_retro], &PLAYER_SDL_COLORS[players[i].color], players[i].rank, players[i].pseudo));
		array_PositionSpecifier_AddElement(&labels.positionSpecifiers, getPseudoAndRankPositionSpecifier(&array_TextLabel_Last(&labels.textLabels)->textZone, players[i].rank));
		
		array_TextLabel_AddElement(&labels.textLabels, createEliminationTurnLabel(renderer, fontHandler->fonts[FONT_retro], &PLAYER_SDL_COLORS[players[i].color], players[i].eliminationTurn));
		array_PositionSpecifier_AddElement(&labels.positionSpecifiers, getEliminationTurnPositionSpecifier(&array_TextLabel_Last(&labels.textLabels)->textZone, players[i].rank));
	}
	return labels;
}


void drawEndGameMenu(SDL_Renderer* renderer, const SDL_Rect rectMenuEndGame, struct endGameMenuTextLabel* labels) {
    SDL_SetRenderDrawColor(renderer, 0,0,0,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 220,220,220,255);
    SDL_RenderFillRect(renderer, &rectMenuEndGame);
    
	for (size_t i=0; i<labels->textLabels.size; ++i) {
		labels->textLabels.elems[i].textZone = adaptPosToRect(&labels->positionSpecifiers.elems[i], &rectMenuEndGame);
		drawTextLabel(renderer, &labels->textLabels.elems[i]);
	}
}

void endGameMenu(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, FontHandler* fontHandler, const Player players[], const size_t nbPlayers) {
	InputProcessor inputProcessor = createInputProcessor();
	const SDL_Rect endGameMenuRect = getEndGameMenuRect(window);
	array_P_Button_AddElement(&inputProcessor.tabButton, createButtonForEndGameMenu(renderer, fontHandler->fonts[FONT_retro], &endGameMenuRect, generalState));
	P_Button* buttonMenuEndGame = array_P_Button_Last(&inputProcessor.tabButton);
	SDL_Rect base100 = {
		.x = 50,
		.y = 99,
		.w = 90,
		.h = 90*buttonMenuEndGame->rect.h/buttonMenuEndGame->rect.w
	};
	PositionSpecifier positionSpecifierButtonRetour = newPositionSpecifier(&base100, POSX_CENTER, POSY_BOTTOM, ASPECT_KEEP_FIT);
	buttonMenuEndGame->rect = adaptPosToRect(&positionSpecifierButtonRetour, &endGameMenuRect);
	buttonMenuEndGame->drawn = false;
	
	struct endGameMenuTextLabel labels =  createLabels(renderer, players, nbPlayers, fontHandler);
	
	drawEndGameMenu(renderer, endGameMenuRect, &labels);
	drawButtonOnRenderer(renderer, buttonMenuEndGame);
	SDL_RenderPresent(renderer);

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
					
					const SDL_Rect rectM = {
						.x=inputElement.data.windowSize.w/10, 
						.y=0, 
						.w=inputElement.data.windowSize.w*80/100, 
						.h=inputElement.data.windowSize.h
					};
					drawEndGameMenu(renderer, rectM, &labels);
					
					buttonMenuEndGame->rect = adaptPosToRect(&positionSpecifierButtonRetour, &rectM);
					buttonMenuEndGame->drawn = false;

					fprintf(stderr, "Resize\n"); fflush(stderr);
				} 
				default:
					break;
				}
			}
		}

		if (!buttonMenuEndGame->drawn) {
			drawButtonOnRenderer(renderer, buttonMenuEndGame);
			SDL_RenderPresent(renderer);
		}
		
		SDL_Delay(10);
	}

	freeInputProcessor(&inputProcessor);
	
	for (size_t i=0; i<labels.textLabels.size; ++i) {
		freeTextLabel(&labels.textLabels.elems[i]);
	}

	array_TextLabel_Free(&labels.textLabels);
	array_PositionSpecifier_Free(&labels.positionSpecifiers);

	freeButton(buttonMenuEndGame);
}
