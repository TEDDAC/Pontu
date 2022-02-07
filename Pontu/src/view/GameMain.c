#include "view/GameMain.h"
#include <stdio.h>
#include "engine/GameInputProcessor.h"
#include "engine/InputElement.h"
#include "engine/TextureHandler.h"
#include "model/Game.h"
#include "model/arrayCoord.h"

#include "view/PiecesDrawer.h"
#include "view/BoardDrawer.h"
#include "view/GameDrawer.h"



SDL_Rect boardRectFromWindowSize(int windowW, int windowH) {
	SDL_Rect boardRect = {.x=windowW/10.0, .y=windowH/10, .w=windowW*8.0/10.0, .h=windowH*8.0/10.0};

	return boardRect;
}

void gameView(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, Player players[], size_t nbPlayers)
{
	if (*generalState != GS_Game) {
		return;
	}
	GameInputProcessor inputProcessor = createGameInputProcessor();
	struct array_Coord interactiveCases = array_Coord_Create();

	Game game = newGame(nbPlayers, players);
	TextureHandler textureHandler = newTextureHandler(renderer);

	int windowW;
	int windowH;

	SDL_GetWindowSize(window, &windowW, &windowH);
	SDL_Rect boardRect = boardRectFromWindowSize(windowW, windowH);

	//Draw 
	drawFullBoard(renderer, &boardRect, &game.board, textureHandler.textures[TEXTURE_Island], textureHandler.textures[TEXTURE_Bridge], textureHandler.textures[TEXTURE_Water]);
	for (int iPlayer=0; iPlayer<nbPlayers; ++iPlayer) {
		drawPiecesPlayer(renderer, &boardRect, game.board.arrPieces, game.board.nbPieces, iPlayer, textureHandler.textures[TEXTURE_PieceRed]);
	}

	SDL_RenderPresent(renderer);


	while(*generalState == GS_Game)
	{
		// Event handling
		InputElement inputElement;
		while (InputType_None != (inputElement = proccessGameInput(&inputProcessor, &boardRect)).type) {

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
					drawMovePiece(renderer, &boardRect, &inputElement.data.move.start, &inputElement.data.move.end, textureHandler.textures[TEXTURE_PieceRed], textureHandler.textures[TEXTURE_Island]);
					SDL_RenderPresent(renderer);
					if (game.phase == GAME_ENDED) {
						*generalState = GS_EndOfGameMenu;
					}
					break;
				}
			
				break;
			}
			case InputType_ClickGame: {
				if(!array_Coord_Contains(&interactiveCases, inputElement.data.coord, *coordEqual)) {
					inputProcessor.selectedCase = newCoord(-1,-1);
				}

				const GameAction actionRealized = clickOnBoard(inputElement.data.coord, &game);
				switch (actionRealized)
				{
				case GameAction_PlacePiece:
					drawPlacePiece(renderer, &boardRect, textureHandler.textures[TEXTURE_PieceViolet], &inputElement.data.coord);
					SDL_RenderPresent(renderer);
					break;
				case GameAction_RemoveBridge:
					drawRemoveBridge(renderer, &boardRect, textureHandler.textures[TEXTURE_Water], &inputElement.data.coord);
					SDL_RenderPresent(renderer);
					break;
				}

				if (actionRealized != GameAction_None) {
					inputProcessor.selectedCase = newCoord(-1,-1);
					if (game.phase == GAME_ENDED) {
						*generalState = GS_EndOfGameMenu;
					}
				}

				break;
			}
			case InputType_None:
			default:
				break;
			}

			array_Coord_Free(&interactiveCases);
			interactiveCases = getInteractiveCases(&game, inputProcessor.selectedCase);
		}

		SDL_Delay(5);
	}

	freeTextureHandler(&textureHandler);
	array_Coord_Free(&interactiveCases);
	freeGameInputProcessor(&inputProcessor);
	
	SDL_Quit();
}
