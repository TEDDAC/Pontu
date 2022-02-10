#include <SDL2/SDL.h>
#include <stdio.h>
#include "view/GameCreationMenu.h"
#include "engine/FontLoader.h"
#include "engine/TextInput.h"

int testCreationMenu(void) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture* picture;
    TextInput textInput;
    int statut = EXIT_FAILURE;
    char* path = "rsrc/img/Lenna.png";
    int i=0;
    int w, h;
    int nbPlayer=1;
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

    if(0 != SDL_SetRenderDrawColor(renderer, 55,120,175,0))  //choisi la couleur avec laquelle travailler
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

    SDL_GetWindowSize(window, &w, &h);
    GeneralState generalState = GS_GameCreationMenu;
    printf("%d/%d\n", w, h);
    gameCreationMenu(renderer, &generalState, fontHandler.fonts[FONT_retro], w, h);

Quit:
    freeFonts(fontHandler);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return statut;
}
