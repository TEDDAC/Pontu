#include "view/GameMain.h"
#include <stdio.h>
#include "engine/GameInputProcessor.h"
#include "engine/InputElement.h"
#include "engine/TextureHandler.h"
#include "engine/arrayButton.h"
#include "engine/arrayTextLabel.h"
#include "engine/TextLabel.h"
#include "model/Game.h"
#include "model/arrayCoord.h"

#include "view/PiecesDrawer.h"
#include "view/BoardDrawer.h"
#include "view/GameDrawer.h"
#include "view/GameInterface.h"

#include "engine/UIElementUtils.h"


PositionSpecifier boardRectPositionSpecifier() {
	SDL_Rect b100 = {
		.x= 50, 
		.y= 50, 
		.w= 80, 
		.h= 80,
	};
	return newPositionSpecifier(&b100, POSX_CENTER, POSY_CENTER, ASPECT_KEEP_FIT);
}

void redrawGameBoard(SDL_Renderer* renderer, const Player players[], const size_t nbPlayers, const TextureHandler* textureHandler, const SDL_Rect* boardRect, const Board* board) {
	drawFullBoard(renderer, boardRect, board, textureHandler->textures[TEXTURE_Island], textureHandler->textures[TEXTURE_Bridge], textureHandler->textures[TEXTURE_Water]);
	for (size_t iPlayer=0; iPlayer<nbPlayers; ++iPlayer) {
		drawPiecesPlayer(renderer, boardRect, board->arrPieces, board->nbPieces, iPlayer, textureHandler, players[iPlayer].color);
	}
}

void gameView(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, Player players[], size_t nbPlayers, FontHandler* fontHandler, AudioHandler* audioHandler)
{
	if (*generalState != GS_Game) {
		return;
	}
	GameInputProcessor gameInputProcessor = createGameInputProcessor();
	struct array_Coord interactiveCases = array_Coord_Create();

	Game game = newGame(nbPlayers, players);
	TextureHandler textureHandler = newTextureHandler(renderer);

	gameInputProcessor.inputProcessor.tabButton = createGameInterfaceButtons(renderer, fontHandler, generalState,audioHandler);
	struct array_TextLabel tabLabel = createGameInterfaceLabels(renderer,fontHandler);

	
	SDL_Rect windowRect = {0,0,0,0};
	SDL_GetWindowSize(window, &windowRect.w, &windowRect.h);
	PositionSpecifier boardRPositionSpecifier = boardRectPositionSpecifier();

	SDL_Rect boardRect = adaptPosToRect(&boardRPositionSpecifier, &windowRect);

	//Draw 
	SDL_SetRenderDrawColor(renderer, 50,10,10, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	redrawGameBoard(renderer, game.arrPlayers, game.nbPlayers, &textureHandler, &boardRect, &game.board);
	for (size_t i=0; i<gameInputProcessor.inputProcessor.tabButton.size; ++i) {
		drawButtonOnRenderer(renderer, &gameInputProcessor.inputProcessor.tabButton.elems[i]);
	}
	for (size_t i=0; i<tabLabel.size; ++i){
		drawTextLabel(renderer,&tabLabel.elems[i]);
	}

	bool needToPresent=true;

	while(*generalState == GS_Game)
	{
		// Event handling
		InputElement inputElement;
		while (InputType_None != (inputElement = proccessGameInput(&gameInputProcessor, &boardRect)).type) {

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
			case InputType_MoveGame: {
				const GameAction actionRealized = moveOnBoard(inputElement.data.move.start, inputElement.data.move.end, &game);
				switch (actionRealized)
				{
				case GameAction_MovePiece:
					drawMovePiece(renderer, &boardRect, &inputElement.data.move.start, &inputElement.data.move.end, &textureHandler, game.arrPlayers[game.currentPlayerID].color);
					needToPresent=true;
					if (game.phase == GAME_ENDED) {
						*generalState = GS_EndOfGameMenu;
					}
					break;
				}
			
				break;
			}
			case InputType_ClickGame: {
				int nbRounds= game.nb_rounds; //Store nb_round 

				if(!array_Coord_Contains(&interactiveCases, inputElement.data.coord, *coordEqual)) {
					gameInputProcessor.selectedCase = newCoord(-1,-1);
				}

				const GameAction actionRealized = clickOnBoard(inputElement.data.coord, &game);
				switch (actionRealized)
				{
				case GameAction_PlacePiece:
					drawPlacePiece(renderer, &boardRect, &textureHandler, game.arrPlayers[(game.currentPlayerID<game.nbPlayers-1) ? game.currentPlayerID+1 : 0].color, &inputElement.data.coord);
					needToPresent=true;
					break;
				case GameAction_RemoveBridge:
					drawRemoveBridge(renderer, &boardRect, textureHandler.textures[TEXTURE_Water], &inputElement.data.coord);
					needToPresent=true;
					break;
				}

				if (actionRealized != GameAction_None) {
					gameInputProcessor.selectedCase = newCoord(-1,-1);
					if (game.phase == GAME_ENDED) {
						*generalState = GS_EndOfGameMenu;
					}
					if(nbRounds != game.nb_rounds) //Redraw nbTurn if has changed 
					{
						
						char newNbTurn[20];
						TextLabel nbTurnTextLabel = tabLabel.elems[2]; //Third element -> Number of nbTurn
						sprintf(newNbTurn,"%d",game.nb_rounds); //Concatenate Turn with nbTurn
						replaceTextAndTextureOfTextLabel(renderer, &nbTurnTextLabel, fontHandler->fonts[FONT_retro], newNbTurn, &nbTurnTextLabel.color);
						SDL_SetRenderDrawColor(renderer, 50,10,10, SDL_ALPHA_OPAQUE);
						SDL_RenderFillRect(renderer,&nbTurnTextLabel.textZone);
						fprintf(stderr,"%s\n",nbTurnTextLabel.text);	
						drawTextLabel(renderer,&nbTurnTextLabel); 
						needToPresent=true;
					}
 
				}

				break;
			}
			case InputType_Window_Resize: {
				windowRect.w = inputElement.data.windowSize.w;
				windowRect.h = inputElement.data.windowSize.h;
				boardRect = adaptPosToRect(&boardRPositionSpecifier, &windowRect);

				redrawGameBoard(renderer, game.arrPlayers, game.nbPlayers, &textureHandler, &boardRect, &game.board);
				for (size_t i=0; i<gameInputProcessor.inputProcessor.tabButton.size; ++i) {
					drawButtonOnRenderer(renderer, &gameInputProcessor.inputProcessor.tabButton.elems[i]);
				}
				for (size_t i=0; i<tabLabel.size; ++i){
					drawTextLabel(renderer,&tabLabel.elems[i]);
				}
				needToPresent=true;
			}
			case InputType_None:
			default:
				break;
			}

			array_Coord_Free(&interactiveCases);
			interactiveCases = getInteractiveCases(&game, gameInputProcessor.selectedCase);
		}

		if(needToPresent)
		{
			SDL_RenderPresent(renderer);
			needToPresent=false;
		}
		SDL_Delay(5);
	}

	for (size_t i = 0; i<nbPlayers; ++i) {
		players[i].rank = game.arrPlayers[i].rank;
		players[i].eliminationTurn = game.arrPlayers[i].eliminationTurn;
	}

	freeTextureHandler(&textureHandler);
	array_Coord_Free(&interactiveCases);
	freeGameInputProcessor(&gameInputProcessor);
}
