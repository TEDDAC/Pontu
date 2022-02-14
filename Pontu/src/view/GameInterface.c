#include "view/GameInterface.h"
#include "engine/TextureLoader.h"
#include <SDL2/SDL_ttf.h>
#include <engine/FontLoader.h>
#include <engine/TextLabel.h>
#include <engine/arrayButton.h>
#include <engine/arrayTextLabel.h>

//void action boutton

void action(P_Button* buttonCaller){
    printf("Bouton menu\n");
    //changeButtonTexture(arg->buttonCaller,arg->texture);
}

struct array_P_Button createGameInterfaceButtons(SDL_Renderer* renderer, FontHandler* fontHandler) {
	SDL_Color menuBorderColor= {0,0,255,255};
    SDL_Color menuBackgroundColor = {0,255,0,255};
    //SDL_Color menuBackgroundColor = {0,0,255,255};

	
	int sizex=20,sizey=20;

	SDL_Texture *menuButtonTexture = createGenericButtonTexture("Menu", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonHoverTexture = createGenericButtonTexture("MenuHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);

    SDL_Texture *settingsButtonTexture = createTextureFromPath(renderer,"rsrc/img/SettingsResized.png");    
    //SDL_Texture *settingsButtonTexture = createGenericButtonTexture("Settings", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);
    SDL_Texture *settingsButtonHoverTexture = createGenericButtonTexture("SettingsHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);

    SDL_Texture *muteButtonTexture = createTextureFromPath(renderer,"rsrc/img/SoundResized.png");
    //SDL_Texture *muteButtonTexture = createGenericButtonTexture("Mute", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);
    SDL_Texture *muteButtonHoverTexture = createGenericButtonTexture("MuteHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);    

	struct array_P_Button buttons = array_P_Button_Create();

	// Menu
	array_P_Button_AddElement(&buttons, createButton(menuButtonTexture, menuButtonHoverTexture,20,20,100,50,&action)); //top left corner (rectangle)
	// Settings
	array_P_Button_AddElement(&buttons, createButton(settingsButtonTexture, settingsButtonHoverTexture, 750,10,50,50,&action)); //top right corner (square or circle)
    // Mute/Unmute
	array_P_Button_AddElement(&buttons, createButton(muteButtonTexture, muteButtonHoverTexture, 825,10,50,50,&action)); //top right cornre (square or circle)

	return buttons;
}

struct array_TextLabel createGameInterfaceLabels(SDL_Renderer* renderer, FontHandler* fontHandler) {
    //Postion text label
    SDL_Point positonNbTurnLabel = {.x=60, .y=850};
    SDL_Point positionTimeLablel = {.x=770, .y=850};

    //Color labal
    SDL_Color colorLabel = {0, 255, 0, 255};


    //Position label
    PositionX_Type positionX = POSX_CENTER;
    PositionY_Type positionY = POSY_CENTER;

    struct array_TextLabel labels = array_TextLabel_Create();

    // Label : Nb Turn
    TextLabel nbTurnLabel = createTextLabel("Turn : ",&positonNbTurnLabel,1,&colorLabel,fontHandler->fonts[FONT_retro],renderer,positionX,positionY);
    // Label : Time of the game
    TextLabel timeLabel = createTextLabel("Time : ",&positionTimeLablel,1,&colorLabel,fontHandler->fonts[FONT_retro],renderer,positionX,positionY);

    //Add TextLabel to the array
    array_TextLabel_AddElement(&labels, nbTurnLabel);
    array_TextLabel_AddElement(&labels, timeLabel);

    return labels;


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
    SDL_Point positonNbTurnLabel = {.x=60, .y=800};
    SDL_Point positionTimeLablel = {.x=770, .y=800};

    //Color labal
    SDL_Color colorLabel = {0, 255, 0, 255};

    //Position label
    PositionX_Type positionX = POSX_CENTER;
    PositionY_Type positionY = POSY_CENTER;



    //SDL_Texture *buttonTexture = createGenericButtonTexture("Menu", NULL, 125, menuBorderColor,menuBackgroundColor,24,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonTexture = createGenericButtonTexture("Menu", fontHandler.fonts[FONT_retro], 125, menuBorderColor,menuBorderColor,24,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonHoverTexture = createGenericButtonTexture("MenuHover", fontHandler.fonts[FONT_retro], 125, menuBorderColor,menuBackgroundColor,24,5,&sizex,&sizey,renderer);

    //Buttons
    P_Button menuButton = createButton(menuButtonTexture, menuButtonHoverTexture,20,20,100,50,&action); //top left corner (rectangle)
    P_Button settingButton = createButton(menuButtonTexture, menuButtonHoverTexture, 750,10,50,50,&action); //top right corner (square or circle)
    P_Button soundButton = createButton(menuButtonTexture, menuButtonHoverTexture, 825,10,50,50,&action); //top right cornre (square or circle)

    //Labels
    TextLabel nbTurnLabel = createTextLabel("Turn : ",&positonNbTurnLabel,1,&colorLabel,fontHandler.fonts[FONT_retro],renderer,positionX,positionY);
    TextLabel timeLabel = createTextLabel("Time : ",&positionTimeLablel,1,&colorLabel,fontHandler.fonts[FONT_retro],renderer,positionX,positionY);



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
        drawTextLabel(renderer,&nbTurnLabel);
        drawTextLabel(renderer,&timeLabel);
        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }



}