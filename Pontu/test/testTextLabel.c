

#include "engine/TextLabel.h"
#include "engine/FontLoader.h"


void testTextLabel() {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture* picture;
    int statut = EXIT_FAILURE;
    char* path = "rsrc/img/Lenna.png";
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

    
    picture = createTextureFromPath(renderer, path);
    FontHandler fontHandler = loadFonts();

    // TextLabel
    SDL_Rect size = {.x=10, .y=10, .w=90, .h=20};

    SDL_Color color = {
        0,0,0,0
    };
    
    TextLabel textLabel = createTextLabel("Salut", &size, &color);
    
    
			    
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
        SDL_RenderClear(renderer);

	    //SDL_RenderCopy(renderer, picture, NULL, NULL);

        drawTextLabel(renderer, &textLabel, fontHandler.fonts[FONT_retro]);

        SDL_RenderPresent(renderer);
            SDL_Delay(500);
        ++i;

            SDL_Delay(20);
    }

Quit:
    freeFonts(fontHandler);
    freeTextLabel(&textLabel);
    if(renderer != NULL)
        SDL_DestroyRenderer(renderer);
    if(window != NULL)
        SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
}

