#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "engine/GeneralState.h"
#include "view/MainMenu.h"
#include "view/MenuEndGame.h"
#include "view/GameCreationMenu.h"
#include "view/GameMain.h"
#include "engine/FontLoader.h"
#include "model/Player.h"

int main(int argc, char *argv[]) {
	SDL_Rect windowSize = {10, 10, 900, 900};

    SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	int statut = EXIT_FAILURE;

	if(SDL_Init(SDL_INIT_VIDEO) != 0) {
		fprintf(stderr, "Error : %s\n", SDL_GetError());
		goto Quit;
	}

	window = SDL_CreateWindow("Pontu",windowSize.x, windowSize.y, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

	char* path = "rsrc/img/PieceViolet.png";
	SDL_Surface* icon = IMG_Load(path);
	if(icon == NULL)
	{
		fprintf(stderr, "WARNNING: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
	//icon->w = 64;
	//icon->h = 64;
	SDL_SetWindowIcon(window, icon);

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    SDL_StopTextInput();

    FontHandler fontHandler = loadFonts();
    AudioHandler audioHandler = newAudioHandler(128, 128, 128);

    GeneralState generalState = GS_MainMenu;
    while(generalState != GS_Quit){
        switch (generalState) {
			case GS_MainMenu:
				mainMenu(renderer,window,&generalState, fontHandler, audioHandler);
				playSFX(SFX_validate_sound, &audioHandler);
				break;
			case GS_GameCreationMenu:{
				int windowW;
				int windowH;

				SDL_GetWindowSize(window, &windowW, &windowH);

				int nbPlayers = 4;
				Player players[] = {
					newPlayer("Bépo", PlayerViolet),
					newPlayer("Azeryty", PlayerBlue),
					newPlayer("Adcsg", PlayerRed),
					newPlayer("qsdfqsdfq", PlayerYellow)
				};
				//players[2] = ;

				bool crashed = gameCreationMenu(renderer, &generalState, &audioHandler, fontHandler.fonts[FONT_PublicPixel], windowW, windowH, players, &nbPlayers);

				/*if (crashed) {
					fprintf(stderr,"sorry");
					exit(-1);
				}*/
				//generalState = GS_Game;

				gameView(&generalState, window, renderer, players, nbPlayers, &fontHandler,&audioHandler);

				//Pour tester le endGameMenu directement
				/*
				generalState = GS_EndOfGameMenu;
				players[0].eliminationTurn = 10;
				players[0].rank = 3;
				players[1].eliminationTurn = 15;
				players[1].rank = 2;
				players[2].eliminationTurn = 0;
				players[2].rank = 1;
				*/

				endGameMenu(&generalState, window, renderer, &fontHandler, players, nbPlayers);
				break;
			}
			case GS_Game: {
				break;
			}
        }
    }

    statut = EXIT_SUCCESS;

Quit:
    freeFonts(fontHandler);
    freeAudioHandler(&audioHandler);
	SDL_FreeSurface(icon);
	if(renderer != NULL) {
		SDL_DestroyRenderer(renderer);
	}
	if(window != NULL) {
		SDL_DestroyWindow(window);
	}
    	SDL_Quit();
	return statut;
}
