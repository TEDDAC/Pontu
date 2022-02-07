#include <stdio.h>
#include <stdlib.h>
#include "engine/GeneralState.h"
#include "view/MainMenu.h"
#include "engine/FontLoader.h"

int main(int argc, char const *argv[]) {
    GeneralState generalState;

    SDL_Window* window = NULL;
	SDL_Rect windowSize = {10, 10, 900, 900};
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

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
	if(!renderer)
	{
		fprintf(stderr, "Erreur : %s", SDL_GetError());
		goto Quit;
	}

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    FontHandler fontHandler = loadFonts();
    AudioHandler audioHandler = newAudioHandler(128, 128, 128);

    generalState = GS_MainMenu;
    while(generalState != GS_Quit){
        switch (generalState) {
			case GS_MainMenu:
				mainMenu(renderer,window,&generalState, fontHandler, audioHandler);
				break;
			/*case GS_EndOfGameMenu:// Coupler avec le menu de jeu
				endGameMenu(&generalState, window, renderer, fontHandler, NULL, 0);
				break;*/
        }
    }

    statut = EXIT_SUCCESS;

Quit:
    freeFonts(fontHandler);
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
    	SDL_Quit();
	return statut;
}
