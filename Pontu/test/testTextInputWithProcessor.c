
#include <SDL2/SDL.h>
#include <stdio.h>
#include "engine/TextureLoader.h"
#include "engine/FontLoader.h"
#include "engine/TextInput.h"
#include "engine/InputProcessor.h"

void testTextInputProcessor() {

	SDL_Rect windowSize = {10, 10, 900, 900};

    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		return;
	}

	window = SDL_CreateWindow("Pontu",windowSize.x, windowSize.y, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		fprintf(stderr, "Erreur : %s", SDL_GetError());
		return;
	}

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }


   	InputProcessor inputProcessor = createInputProcessor();

	bool needToPresent = true;

    FontHandler fontHandler = loadFonts();    
    SDL_StopTextInput();

    TextInput tI;
    array_TextInput_AddElement(&inputProcessor.tabTextInput, tI);
    TextInput* textInput = array_TextInput_Last(&inputProcessor.tabTextInput);
    SDL_Rect size = {.x=10, .y=10, .w=90, .h=20};

    if(!initTextInput(textInput, &size, NULL, fontHandler.fonts[FONT_PublicPixel]))
    {
	fprintf(stderr, "WARNING: can't init TextInput\n");
    return;
    }

    drawTextInputOnRenderer(renderer, textInput);

	bool quit = false;
	while(!quit)
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
				case InputType_Window_Resize: {

					/*const SDL_Rect rectM = {
						.x=inputElement.data.windowSize.w/10,
						.y=0,
						.w=inputElement.data.windowSize.w*80/100,
						.h=inputElement.data.windowSize.h
					};*/
					
					break;
				}
				case InputType_TextInput:
					drawTextInputOnRenderer(renderer, inputElement.data.textInput);
					needToPresent = true;
				default:
					break;
				}
			}
		}



		if (needToPresent) {
			SDL_RenderPresent(renderer);
			needToPresent = false;
		}

		SDL_Delay(10);
	}

	fprintf(stderr, "Texte tapé : %s\n", textInput->value);

	freeInputProcessor(&inputProcessor);
}
