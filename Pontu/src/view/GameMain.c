#include "view/GameMain.h"
#include <stdio.h>
#include "engine/GameInputProcessor.h"
#include "engine/InputElement.h"
#include "engine/TextureHandler.h"
#include "model/Game.h"
#include "model/arrayCoord.h"
#include "debug/printer.h"

SDL_Rect boardRectFromWindowSize(int windowW, int windowH) {
	SDL_Rect boardRect = {.x=windowW/10.0, .y=windowH/10, .w=windowW*8.0/10.0, .h=windowH*8.0/10.0};

	return boardRect;
}

void gameView(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, Player players[], size_t nbPlayers)
{
	if (*generalState != GS_Game) {
		return ;
	}
	GameInputProcessor inputProcessor = createGameInputProcessor();
	struct array_Coord interactiveCases = array_Coord_Create();

	Game game = newGame(players, nbPlayers);
	TextureHandler textureHandler = newTextureHandler(renderer);

	int windowW;
	int windowH;

	SDL_GetWindowSize(window, &windowW, &windowH);
	SDL_Rect boardRect = boardRectFromWindowSize(windowW, windowH);

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
			case InputType_MoveGame:
				fprintf(stderr, "Move on board\n");
				fprintf(stderr, "From (%d; %d)\n", inputElement.data.move.start.x, inputElement.data.move.start.y);
				fprintf(stderr, "To (%d; %d)\n", inputElement.data.move.end.x, inputElement.data.move.end.y);

				moveOnBoard(inputElement.data.move.start, inputElement.data.move.end, &game);

				
				break;
			case InputType_ClickGame:
				fprintf(stderr, "Clic on board (%d; %d)\n", inputElement.data.coord.x, inputElement.data.coord.y);
				fprintf(stderr, "\tSelected case : (%d; %d)\n", inputProcessor.selectedCase.x, inputProcessor.selectedCase.y);

				if(!array_Coord_Contains(&interactiveCases, inputElement.data.coord, *coordEqual)) {
					fprintf(stderr, "\tselected case reset\n");
					inputProcessor.selectedCase = newCoord(-1,-1);
				}

				if (clickOnBoard(inputElement.data.coord, &game)) {
					fprintf(stderr, "\tselected case reset\n");
					inputProcessor.selectedCase = newCoord(-1,-1);
				}


				break;
			case InputType_None:
			default:
				break;
			}

			array_Coord_Free(&interactiveCases);
			interactiveCases = getInteractiveCases(&game, inputProcessor.selectedCase);
			fprintf(stderr, "Interactive cases : {");
			array_Coord_Foreach(&interactiveCases, *printCoord);
			fprintf(stderr, "}\n");
		}

		fflush(stderr);

		// Drawing
		drawGame(renderer, &windowSize, &boardRect, &game, &textureHandler);

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}

Quit:
	freeTextureHandler(&textureHandler);
	array_Coord_Free(&interactiveCases);
	
	SDL_Quit();
	return statut;
}
