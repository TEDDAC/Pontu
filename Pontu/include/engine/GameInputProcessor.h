/**
 * \file GameInputProcessor.h
 * \brief Define a structure, GameInputProcessor and functions to convert SDL_event to envent for Pontu
 * \author Martin Rouault
 * \date 06/12/2021
 */

#ifndef GAME_INPUT_PROCESSOR_INCLUDED
#define GAME_INPUT_PROCESSOR_INCLUDED

#include "engine/Button.h"
#include "engine/arrayButton.h"
#include "engine/InputElement.h"
#include "model/Coord.h"

/**
 * \struct GameInputProcessor
 * \brief Contains datas useful to handle input
 */
typedef struct
{
	struct array_P_Button tabButton;
	Coord selectedCase; ///< A case in Board (used to handle move actions) , (-1;-1) si inexistant
} GameInputProcessor;


/**
 * \brief Create a new input processor
 *
 * \return A new input processor
 */
GameInputProcessor createGameInputProcessor();

/**
 * @brief Free a game input processor
 * 
 * @param gameInputProcessor the game input processor to free (do not use after freeing)
 */
void freeGameInputProcessor(GameInputProcessor* gameInputProcessor);

/**
 * \brief Convert a screen coord into a model Coord
 * 
 * \param [in] point Screen coordinates
 * \param [in] boardRect The game's board's rect
 * \return Game coordinate from point
 */
Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect);

/**
 * \brief Poll and convert SDL_Events into specific event for Pontu
 * 
 * \param [in, out] GameinputProcessor The input processor which keeps a state of input in between calls
 * \param [in] boardRect The game's board's rect
 * \return InputElement : an event for Pontu
 */
InputElement proccessGameInput(GameInputProcessor* gameInputProcessor, const SDL_Rect* boardRect);

#endif // GAME_INPUT_PROCESSOR_INCLUDED
