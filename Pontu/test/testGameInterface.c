#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <engine/FontLoader.h>
//#include "engine/TextureLoader.h"
//#include "view/GameInterface.h"

int testGameInterface()
{
	
	SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *buttonTexture= NULL;
    int statut = EXIT_FAILURE;

    //Initialiser TTF
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'inistialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    //Initialize SDL 
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

     //fenetre
    window = SDL_CreateWindow("Fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,600, SDL_WINDOW_SHOWN);
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

    if(0 != SDL_SetRenderDrawColor(renderer, 255,0,0,0))  //choisi la couleur avec laquelle travailler
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
        goto Quit;
    }

    if(0 != SDL_RenderClear(renderer))  //efface le rendu en le repeignant avec la couleur choisi
    {
        fprintf(stderr, "Erreur SDL_SetRenderDrawColor: %s\n", SDL_GetError());
        goto Quit;
    }

    //SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    FontHandler fontHandler=loadFonts();

    drawButtons(renderer,fontHandler);

    SDL_RenderPresent(renderer);
    SDL_Delay(3000);

    //TTF_Quit();
    if(!freeFonts(fontHandler))
    {
        fprintf(stderr,"Erreur free font : %s\n", TTF_GetError());
    }


    Quit:
    /*
    if(NULL != texture)
        SDL_DestroyTexture(texture);
    */
    freeFonts(fontHandler);
    if(NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if(NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
    




}