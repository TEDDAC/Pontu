#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"
#include "engine/TextureHandler.h"
#include "model/Game.h"
#include "model/arrayCoord.h"
#include "view/GameDrawer.h"
#include "engine/ArrayUtils.h"
#include "debug/printer.h"

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Rect windowSize = {10, 10, 600, 600};
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("Pontu",windowSize.x, windowSize.y, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN);
	if (!window)
	{
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;   
	}

	renderer = SDL_CreateRenderer(window,-1,0);
	if(!renderer)
	{
		fprintf(stderr, "Erreur : %s", SDL_GetError());
		goto Quit;
	}

	InputProcessor inputProcessor = {.selectedCase = {.x=-1, .y=-1}};
	struct array_Coord interactiveCases = array_Coord_Create();

	int wBoardRect=99*3, hBoardRect=99*3;
	SDL_Rect boardRect = {.x=windowSize.w/2 - wBoardRect/2, .y=windowSize.h/2 - hBoardRect/2, .w=wBoardRect, .h=99*3};
	const char* pseudos[] = {"Azerty","Bépo"};
	Game game = newGame(2, pseudos);
	TextureHandler textureHandler = newTextureHandler(renderer);


	bool quit = false;
	while(!quit)
	{
		// Event handling
		InputElement inputElement;
		while (InputType_None != (inputElement = proccessInput(&inputProcessor, &boardRect)).type) {

			switch (inputElement.type)
			{
			case InputType_ActivateUI:
				switch (inputElement.data.uiAction)
				{
				case UIAction_Quit:
					quit = true;
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
			fflush(stderr);
		}
		


		// Drawing
		drawGame(renderer, &windowSize, &boardRect, &game, &textureHandler);

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}

	statut = EXIT_SUCCESS;

Quit:
	freeTextureHandler(&textureHandler);
	array_Coord_Free(&interactiveCases);
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
	
	SDL_Quit();
	return statut;
}
