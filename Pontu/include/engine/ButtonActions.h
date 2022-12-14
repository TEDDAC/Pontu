#ifndef BUTTON_ACTION_INCLUDED
#define BUTTON_ACTION_INCLUDED

#include "engine/Button.h"
#include "engine/AudioHandler.h"
#include <SDL2/SDL.h>
#include "engine/arrayButton.h"

/**
 * @brief Args for the SoundButton
 */
typedef struct 
{
    AudioHandler* audio; //Audio from which we change masterVolume
    SDL_Renderer* renderer; 
}argsSoundButton; 

void action_none(P_Button* caller);

void action_print(P_Button* caller);

/**
 * @brief Button handle which set a generalState to GS_MainMenu
 * @param caller The button clicked
 */
void action_setStateToMainMenu(P_Button* caller);

/**
 * @brief Button handle wich mute and unmute the master volume
 * @param caller The button clicked
 */
void action_muteSound(P_Button* caller);

/**
 * @brief Button handle which show Settings 
 * @param caller The button clicked
 */
void action_showSettings(P_Button* caller);

#endif //BUTTON_ACTION_INCLUDED