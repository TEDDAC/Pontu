/**
 * \file InputProcessor.h
 * \brief Define a structure, InputProcessor and functions to convert SDL_event to envent for Pontu
 * \author Martin Rouault
 * \date 06/12/2021
 */

#ifndef INPUT_PROCESSOR_INCLUDED
#define INPUT_PROCESSOR_INCLUDED

#include "engine/Button.h"
#include "engine/InputElement.h"
#include "model/Coord.h"

/**
 * \struct InputProcessor
 * \brief Contains datas useful to handle input
 */
typedef struct
{
	//ArrayButton tabButton;
	Coord selectedCase; ///< A case in Board (used to handle move actions) , (-1;-1) si inexistant
} InputProcessor;

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
 * \param [in, out] inputProcessor The input processor which keeps a state of input in between calls
 * \param [in] boardRect The game's board's rect
 * \return InputElement : an event for Pontu
 */
InputElement proccessInput(InputProcessor* inputProcessor, const SDL_Rect* boardRect);

#endif // INPUT_PROCESSOR_INCLUDED
