#include "view/GameInterface.h"
#include "engine/TextureLoader.h"
#include <SDL2/SDL_ttf.h>
#include <engine/FontLoader.h>
#include <engine/TextLabel.h>
#include <engine/arrayButton.h>
#include <engine/arrayTextLabel.h>
#include <engine/ButtonActions.h>



struct array_P_Button createGameInterfaceButtons(SDL_Renderer* renderer, FontHandler* fontHandler, GeneralState* generalState, AudioHandler audioHandler) {
    	
    SDL_Color menuBorderColor= {0,0,255,255};
    SDL_Color menuBackgroundColor = {0,255,0,255};

	int sizex=20,sizey=20;

	SDL_Texture *menuButtonTexture = createGenericButtonTexture("Menu", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);
    SDL_Texture *menuButtonHoverTexture = createGenericButtonTexture("MenuHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);

    SDL_Texture *settingsButtonTexture = createTextureFromPath(renderer,"rsrc/img/SettingsResized.png");    
    SDL_Texture *settingsButtonHoverTexture = createGenericButtonTexture("SettingsHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);

    //SDL_Texture *muteButtonTexture = createTextureFromPath(renderer,"rsrc/img/SoundResized.png");
    SDL_Texture *muteButtonTexture = createTextureFromPath(renderer,"rsrc/img/NewSoundResized.png");
    SDL_Texture *muteButtonHoverTexture = createGenericButtonTexture("MuteHover", fontHandler->fonts[FONT_retro], 15, menuBorderColor,menuBackgroundColor,13,5,&sizex,&sizey,renderer);    

	struct array_P_Button buttons = array_P_Button_Create();

	// Menu
	array_P_Button_AddElement(&buttons, createButton(menuButtonTexture, menuButtonHoverTexture,20,20,100,50,&action_setStateToMainMenu)); //top left corner (rectangle)
	array_P_Button_Last(&buttons)->arg = (void*)generalState;

    // Settings
	array_P_Button_AddElement(&buttons, createButton(settingsButtonTexture, settingsButtonHoverTexture, 750,10,50,50,&action_print)); //top right corner (square or circle)

    // Mute/Unmute
    argsSoundButton argsSoundButt = {audioHandler, renderer};
	array_P_Button_AddElement(&buttons, createButton(muteButtonTexture, muteButtonHoverTexture, 825,10,50,50,&action_muteSound)); //top right cornre (square or circle)
    array_P_Button_Last(&buttons)->arg = (void*)&argsSoundButt;
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

