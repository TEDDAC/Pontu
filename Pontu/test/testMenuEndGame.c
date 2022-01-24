

#include "view/MenuEndGame.h"
#include "engine/FontLoader.h"
#include "model/Player.h"

void testMenuEndGame() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture* picture;
    int statut = EXIT_FAILURE;
    int i=0;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_INIT: %s\n", SDL_GetError());
        goto Quit;
    }

    //fenetre
    window = SDL_CreateWindow("Fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,480, SDL_WINDOW_SHOWN);
    if(window == NULL)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow: %s\n", SDL_GetError());
        goto Quit;
    }

    //rendu
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
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

    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    FontHandler fontHandler = loadFonts();
			    
    SDL_RenderPresent(renderer);
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            case SDL_MOUSEBUTTONUP:
                break;
            }
        }
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderClear(renderer);

        SDL_Rect rect = {.x=20, .y=0, .w=300, .h=480};
        SDL_Color color = {0,0,0,0};
        Player players[] = {newPlayer("Bépo", color), newPlayer("Azerty", color)};
        players[0].eliminationTurn = 10;
        players[1].eliminationTurn = 10;
        players[0].rank = 1;
        players[1].rank = 2;
        drawEndGameMenu(renderer, players, 2, &rect, &fontHandler);

        SDL_RenderPresent(renderer);
            SDL_Delay(500);
        ++i;

            SDL_Delay(20);
    }

Quit:
    freeFonts(fontHandler);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

