#ifndef MENU_FIN_INCLUDED
#define MENU_FIN_INCLUDED

#include <SDL2/SDL.h>
#include "model/Player.h"
#include "engine/FontLoader.h"

#include "engine/Button.h"
#include "engine/TextureLoader.h"
#include "engine/GeneralState.h"

/**
 * @brief Handle end game menu
 * 
 * @param generalState The general state of the application (will be mutate to GS_MAIN_MENU)
 * @param window Application's menu
 * @param renderer Application's renderer
 * @param fontHandler Application's fonts handler
 * @param players An array of player with rank and elimination turn set
 * @param nbPlayers number of player in players 
 */
void endGameMenu(GeneralState* generalState, SDL_Window* window, SDL_Renderer* renderer, FontHandler* fontHandler, const Player players[], const size_t nbPlayers);


#endif // MENU_FIN_INCLUDED
