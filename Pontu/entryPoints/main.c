#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"
#include "engine/TextureHandler.h"
#include "model/Game.h"
#include "view/BoardDrawer.h"

int main(int argc, char* argv[])
{
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("Pontu",10,10,600,600,SDL_WINDOW_SHOWN);
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
	SDL_Rect boardRect = {.x=20, .y=20, .w=99*3, .h=99*3};
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
				moveOnBoard(inputElement.data.move.start, inputElement.data.move.end, &game);
				break;
			case InputType_ClickGame:
				fprintf(stderr, "Clic on board (%d; %d)\n", inputElement.data.coord.x, inputElement.data.coord.y);
				fflush(stderr);
				if (cliqueOnBoard(inputElement.data.coord, &game)) {
					inputProcessor.selectedCase = newCoord(-1,-1);
				}
				break;
			case InputType_None:
			default:
				break;
			}
		}
		


		// Drawing
		drawBoard(renderer, &boardRect, &game.board, textureHandler.textures[TEXTURE_Island],  textureHandler.textures[TEXTURE_Bridge], textureHandler.textures[TEXTURE_Water]);

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}

	statut = EXIT_SUCCESS;

Quit:
	freeTextureHandler(&textureHandler);
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
	
	SDL_Quit();
	return statut;
}