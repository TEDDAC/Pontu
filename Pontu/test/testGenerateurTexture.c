#include "engine/TextureLoader.h"
#include <string.h>

int testGenerateurTexture(){
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



    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }

    // load font.ttf at size 16 into font
    TTF_Font *retroFont;
    int size = 100*100/88;
    char* string = "Pontu";
    retroFont=TTF_OpenFont("rsrc/font/retro/retro.TTF", size);
    if(!retroFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
    }
    SDL_Color White = {255, 255, 255};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(retroFont, string, White);

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

    int minx,maxx,miny,maxy,advance;
    if(TTF_GlyphMetrics(retroFont,string,&minx,&maxx,&miny,&maxy,&advance)==-1)
        printf("%s\n",TTF_GetError());
    else {
        printf("minx    : %d\n",minx);
        printf("maxx    : %d\n",maxx);
        printf("miny    : %d\n",miny);
        printf("maxy    : %d\n",maxy);
        printf("advance    : %d\n",advance);
    }

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = strlen(string)*size*2/3; // controls the width of the rect
    Message_rect.h = size; // controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

    SDL_RenderPresent(renderer);

    SDL_bool quit = SDL_FALSE;
    SDL_Event event;
    while(!quit)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                quit = SDL_TRUE;
                break;
            }
        }
    }

Quit:
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    SDL_Quit();
    TTF_Quit();
    return statut;
}
