

#include "view/MenuEndGame.h"
#include "engine/FontLoader.h"
#include "model/Player.h"
#include "engine/InputProcessor.h"
#include "engine/InputElement.h"

void testMenuEndGame() {
	SDL_Window *window = NULL;
	SDL_Rect windowSize = {10, 10, 1100, 600};
	SDL_Renderer *renderer = NULL;

	if(0 != SDL_Init(SDL_INIT_VIDEO))
	{
		fprintf(stderr, "Erreur SDL_INIT: %s\n", SDL_GetError());
		goto Quit;
	}

	//fenetre
	window = SDL_CreateWindow("Fenêtre", windowSize.x, windowSize.y, windowSize.w, windowSize.h, SDL_WINDOW_SHOWN);
	if(window == NULL)
	{
		fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
		goto Quit;
	}

	//rendu
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	if(renderer == NULL)
	{
		fprintf(stderr, "Erreur SDL_CreateRenderer: %s\n", SDL_GetError());
		goto Quit;
	}

	//Fonts
	if(TTF_Init() == -1)
	{
	fprintf(stderr, "Erreur: TTF_Init: %s\n", TTF_GetError());
	goto Quit;
	}

	if(0 != SDL_SetRenderDrawColor(renderer, 0,0,0,0))  //choisi la couleur avec laquelle travailler
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
		goto Quit;
	}

	if(0 != SDL_RenderClear(renderer))  //efface le rendu en le repeignant avec la couleur choisi
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
		goto Quit;
	}

	if(0 != SDL_SetRenderDrawColor(renderer, 255,255,255,255))  //choisi la couleur avec laquelle travailler
	{
		fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
		goto Quit;
	}


	FontHandler fontHandler = loadFonts();
				
	SDL_RenderPresent(renderer);
	GeneralState generalState = GS_EndOfGameMenu;

	SDL_Color color = {0,0,0,0};
	Player players[2] = {newPlayer("Bépo", color), newPlayer("Azerty", color)};
	players[0].eliminationTurn = 10;
	players[1].eliminationTurn = 10;
	players[0].rank = 1;
	players[1].rank = 2;

	endGameMenu(&generalState, window, renderer, &fontHandler, players, 2);

Quit:
	freeFonts(fontHandler);
	if(renderer != NULL)
		SDL_DestroyRenderer(renderer);
	if(window != NULL)
		SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}

