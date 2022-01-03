#include <SDL2/SDL.h>
#include <stdio.h>
#include "engine/Button.h"

//gcc test.c -I ../include $(sdl2-config --cflags --libs)

void action(P_ButtonArg* arg){
    printf("Clické\n");
    changeButtonTexture(arg->buttonCaller,arg->texture);
}

int main(int argc, char const *argv[]) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    int statut = EXIT_FAILURE;

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
    SDL_RenderPresent(renderer);

    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

    //créer la texture du bonton
    SDL_Texture* buttonTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,20,20);
    SDL_SetRenderTarget(renderer, buttonTexture);
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_Rect buttonRect = {.x = 0,.y = 0,.w = 50,.h = 70};
    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_Texture* blueTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,20,20);
    SDL_SetRenderDrawColor(renderer, 0,0,255,255);
    SDL_SetRenderTarget(renderer, blueTexture);
    SDL_RenderFillRect(renderer, &buttonRect);

    P_Button button = createButton(buttonTexture,blueTexture ,20, 20, 70, 50, &action);
    P_ButtonArg arg;
    arg.buttonCaller = &button;

    SDL_Texture* violetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,20,20);
    SDL_SetRenderDrawColor(renderer, 150,75,200,255);
    SDL_SetRenderTarget(renderer, violetTexture);
    SDL_RenderFillRect(renderer, &buttonRect);

    SDL_SetRenderTarget(renderer, NULL);
    arg.texture = violetTexture;
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
                if(isHover(&button,event.button.x,event.button.y))
                button.onClick(&arg);
                break;
            case SDL_MOUSEMOTION:
                //on vérifie à chaque tour ou est la souris, drawButtonOnRenderer choisit la bonne texture à afficher
                isHover(&button,event.motion.x,event.motion.y);
                break;
            }
        }
        drawButtonOnRenderer(renderer,&button);
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
