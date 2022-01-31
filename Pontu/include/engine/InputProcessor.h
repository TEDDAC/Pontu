/**
 * \file InputProcessor.h
 * \brief Define a structure, InputProcessor and functions to convert SDL_event to envent for Pontu
 * \author Martin Rouault
 * \date 06/12/2021
 */

#ifndef INPUT_PROCESSOR_INCLUDED
#define INPUT_PROCESSOR_INCLUDED

#include "engine/Button.h"
#include "engine/arrayButton.h"
#include "engine/InputElement.h"

/**
 * \struct InputProcessor
 * \brief Contains datas useful to handle input
 */
typedef struct
{
	struct array_P_Button tabButton;
} InputProcessor;


/**
 * \brief Create a new input processor
 *
 * \return A new input processor
 */
InputProcessor createInputProcessor();

/**
 * \brief Poll and convert SDL_Events into specific event for Pontu
 * 
 * \param [in, out] inputProcessor The input processor which keeps a state of input in between calls
 * \return InputElement : an event for Pontu
 */
InputElement proccessInput(InputProcessor* inputProcessor);

#endif // INPUT_PROCESSOR_INCLUDED
