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



//move pion

//delete pion

//draw menu Ponton (top left corner)
/**
 * \brief Draw different buttons on the game interface : menu, setting, sound, nbTurn, and timers
 * param Renderer 
 */
void drawButtons(SDL_Renderer* renderer,FontHandler fontHandler);

//draw setting button (top right corner)

//draw sound button (top right corner)

//draw nbTurn (bottom left corner)

//draw timer (bottom right corner)



#endif

