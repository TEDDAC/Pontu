/**
 * \file BoardDrawer.h
 * \brief Define functions to draw the game
 * \author Martin Rouault
 * \date 16/12/2021
 */

#ifndef BOARD_DRAWER_INCLUDED
#define BOARD_DRAWER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>
#include "model/Board.h"

/**
 * \brief Draw the board (water, islands and bridges)
 * 
 * \param renderer The renderer
 * \param boardRect The rect were the board is drawn
 * \param board The game's board (for bridges)
 * \param island Texture for islands
 * \param bridge Texture for bridges
 * \param water Texture for water
 * \return true I don't know what to return
 */
bool drawBoard(SDL_Renderer* renderer, const SDL_Rect* boardRect, const Board* board, SDL_Texture* island, SDL_Texture* bridge, SDL_Texture* water);


#endif
