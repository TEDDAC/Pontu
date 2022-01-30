#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include "engine/Button.h"
#include "engine/FontLoader.h"
#include "view/MainMenu.h"

int testDrawMainMenu(){
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;

    if(0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_INIT: %s\n", SDL_GetError());
        goto Quit;
    }

    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    //fenetre
    window = SDL_CreateWindow("Fenêtre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640,480, SDL_WINDOW_MAXIMIZED);
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

    //Initialisation

    P_Button* buttons = NULL;
    unsigned int nb = 0;
    FontHandler fontHandler = loadFonts();

    int window_w, window_h;
    SDL_GetWindowSize(window,&window_w,&window_h);

    SDL_Rect rect = {.x = 0, .y = 0, .w = window_w, .h = window_h};
    if(!(buttons = drawMainMenu(renderer,fontHandler,&nb,&rect))){
        fprintf(stderr, "Le menu principale ne s'est pas déssiné correctement\n");
        return statut;
    }

    SDL_SetRenderDrawColor(renderer, 0,0,0,0);
    SDL_RenderClear(renderer);
    bool quit = false;
    SDL_Event event;
    buttons[2].arg = &quit;
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
                if(isHover(buttons,event.button.x,event.button.y))
                    printf("Nouvelle partie\n");
                if(isHover(&(buttons[2]),event.motion.x,event.motion.y)){
                    buttons[2].onClick(&(buttons[2]));
                }
                break;
            case SDL_MOUSEMOTION:
                isHover(&(buttons[0]),event.motion.x,event.motion.y);
                isHover(&(buttons[1]),event.motion.x,event.motion.y);
                isHover(&(buttons[2]),event.motion.x,event.motion.y);
                break;
            default:
                break;
            }
        }

        /*for(int i=0;i<nb;i++){
            drawButtonOnRenderer(renderer,&(buttons[i]));
            printf("%d\n",i);
        }*/
        drawButtonOnRenderer(renderer,&(buttons[0]));
        drawButtonOnRenderer(renderer,&(buttons[1]));
        drawButtonOnRenderer(renderer,&(buttons[2]));
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }

Quit:
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
