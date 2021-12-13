#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"

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
	SDL_Rect rectBoard = {.x=20, .y=20, .w=99, .h=99};

	bool quit = false;
	while(!quit)
	{
		// Event handling
		InputElement inputElement;
		while (InputType_None != (inputElement = proccessInput(&inputProcessor, &rectBoard)).type) {
			
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

				break;
			case InputType_ClickGame:
				break;
			case InputType_None:
			default:
				break;
			}
		}
		


		// Drawing
		

		SDL_RenderPresent(renderer);

		SDL_Delay(20);
	}

	statut = EXIT_SUCCESS;

Quit:
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
	SDL_Quit();
	return statut;
}