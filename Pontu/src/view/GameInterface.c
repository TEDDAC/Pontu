#include "view/GameInterface.h"
#include "engine/TextureLoader.h"
#include <SDL2/SDL_ttf.h>
#include <engine/FontLoader.h>
#include <engine/TextLabel.h>

//void action boutton

void action(P_Button* buttonCaller){
    printf("Bouton menu\n");
    //changeButtonTexture(arg->buttonCaller,arg->texture);
}


void drawButtons(SDL_Renderer* renderer, FontHandler fontHandler)
{
	//DRAW MENU BUTTON (TOP RIGHT CORNER)

    SDL_bool quit = SDL_FALSE;
    SDL_Event event;

	int sizex=20,sizey=20;

    /*
    
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'inistialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }


    TTF_Font* retroFont = NULL;
	
	//load ttf 
    int fontSize = 100;
    int size = fontSize*100/88;
    retroFont=TTF_OpenFont("rsrc/font/retro/retro.TTF", size);
    if(!retroFont) {
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
    }
    */



    
    //FontHandler fontHandler=loadFonts();

    //Menu Button's colors 
    SDL_Color menuBorderColor= {0,0,255,255};
    SDL_Color menuBackgroundColor = {0,255,0,255};

    //Postion text label
    //SDL_Point pos 


    //SDL_Texture *buttonTexture = createGenericButtonTexture("Menu", NULL, 125, menuBorderColor,menuBackgroundColor,24,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonTexture = createGenericButtonTexture("Menu", fontHandler.fonts[FONT_retro], 125, menuBorderColor,menuBorderColor,24,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonHoverTexture = createGenericButtonTexture("MenuHover", fontHandler.fonts[FONT_retro], 125, menuBorderColor,menuBackgroundColor,24,5,&sizex,&sizey,renderer);

    P_Button menuButton = createButton(menuButtonTexture, menuButtonHoverTexture,20,20,100,50,&action); //top left corner (rectangle)
    P_Button settingButton = createButton(menuButtonTexture, menuButtonHoverTexture, 750,10,50,50,&action); //top right corner (square or circle)
    P_Button soundButton = createButton(menuButtonTexture, menuButtonHoverTexture, 825,10,50,50,&action); //top right cornre (square or circle)
    //TextLabel nbTurn = createTextLabel("Turn",)


    //bool drawButtonOnRenderer(SDL_Renderer* renderer, P_Button* button);

	//P_Button createButton(SDL_Texture* texture, SDL_Texture* hoverTexture ,const int coordx, const int coordy, const int sizex, const int sizey, void (*onClick)(P_ButtonArg* arg));

    //Create Button Texture
    //SDL_Texture* createGenericButtonTexture(char* text, TTF_Font* font, int fontSize, SDL_Color border_color, SDL_Color background_color,int thickness, int padding, int* sizex, int* sizey, SDL_Renderer* renderer);


    SDL_Texture* violetTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,20,20);
    SDL_SetRenderDrawColor(renderer, 150,75,200,255);
    SDL_SetRenderTarget(renderer, violetTexture);
    //SDL_RenderFillRect(renderer, &buttonRect);

    SDL_SetRenderDrawColor(renderer,255,0,0,0);
    SDL_SetRenderTarget(renderer, NULL);

    SDL_RenderClear(renderer);
    
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
                //if(isHover(&menuButton,event.button.x,event.button.y))
                if(isHover(&menuButton))
                menuButton.onClick(&menuButton);
                break;
            case SDL_MOUSEMOTION:
                //on vérifie à chaque tour ou est la souris, drawButtonOnRenderer choisit la bonne texture à afficher
                //isHover(&menuButton,event.motion.x,event.motion.y);
                isHover(&menuButton);
                break;
            }
        }

        drawButtonOnRenderer(renderer,&menuButton);
        drawButtonOnRenderer(renderer,&settingButton);
        drawButtonOnRenderer(renderer,&soundButton);
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }




}