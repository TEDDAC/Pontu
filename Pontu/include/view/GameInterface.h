/**
 * \file GameInterface.h
 * \breif Interface of game
 * \author Jacques Thomas
 * \date 24/01/20222
 */

#ifndef GAME_INTERFACE_INCLUDED
#define GAME_INTERFACE_INCLUDED

#include <SDL2/SDL.h>
#include "engine/Button.h" 
#include <engine/FontLoader.h>
#include "engine/arrayButton.h"
#include "engine/GeneralState.h"
#include "engine/AudioHandler.h"


/**
 * \brief Create an array of P_Button for the game interface
 * \param renderer The renderer on which we create P_buttons  
 * \param fontHandler The fontHandler to apply 
 * \return an array of P_Button to draw on the renderer
 */
struct array_P_Button createGameInterfaceButtons(SDL_Renderer* renderer, FontHandler* fontHandler, GeneralState* generalState, AudioHandler* audioHandler);


/**
 * \brief Create an array of TextLabel for the game interface
 * \param renderer The renderer on which we create TextLabel
 * \param fontHandler The fontHandler to apply
 * \return an array of TextLabel to draw on the renderer
 */
struct array_TextLabel createGameInterfaceLabels(SDL_Renderer* renderer, FontHandler* fontHandler);

#endif

