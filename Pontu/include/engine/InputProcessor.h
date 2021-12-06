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
 * \struct
 */
typedef struct
{
	ArrayButton tabButton;
	Coord selectedCase; ///< Board , (-1;-1) si inexistant
} InputProcessor;

Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect);

InputElement proccessInput(InputProcessor* inputProcessor, const SDL_Rect* boardRect);

#endif // INPUT_PROCESSOR_INCLUDED
