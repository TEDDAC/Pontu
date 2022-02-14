/**
 * \file TextInput.h
 * \brief Basic TextInput
 * \author Allan Point
 * \date 05/01/2022
 * \copyright CECILL
 */

#ifndef TEXT_INPUT_INCLUDED
#define TEXT_INPUT_INCLUDED

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>
#include <stdbool.h>
#include "engine/FontUtils.h"


/**
 * \struct TextInput
 * \typedef
 * \brief A text-inputable zone representation
 * \author Allan Point
 * \date 05/01/2022
 */
typedef struct
{
	char* value;
	Sint32 cursorPosition;
	
	SDL_Rect size;
	bool isActive;
	SDL_Color textColor;
	TTF_Font* textFont;
}TextInput;

/**
 * \brief Add a character on the right place on the textInput
 * \param[in,out]	textInput	Memmory address of the TextInput to modify
 * \param[in]	charToAdd	Character to add at the curent cursor position
 * \return True if all goes right. Else false.
 * \author Allan Point
 * \date 05/01/2022
 */
bool addCharacterToInputTextValueAtCursor(TextInput* textInput, const char charToAdd);

/**
 * \brief Remove a character from the TextInput
 * \param[in,out]	textInput	TextInput to modify
 * \return True if all goes right. Esle false.
 * \author Allan Point
 * \date 05/01/2022
 */
bool removeCharacterToInputTextValueAtCursor(TextInput* textInput);

/**
 * \brief Draw a text input on a renderer
 * \param[in,out]	renderer	The renderer to draw on
 * \param[in]	textInput	The TextInput to be drawn
 * \return True on success. Esle false;
 * \author Allan POINT
 * \date 05/01/2022
 */
bool drawTextInputOnRenderer(SDL_Renderer* renderer, const TextInput* textInput);

/**
 * \brief Initalize a TextInput
 * \details value=""
 * \details cursorPosition=0
 * \details size is given by user
 * \details isActive=false
 * \details By default, color is true black, else textColor is given by user
 * \details textFont is given by user
 * \param[out]	textInput	Address of a TextInput to init
 * \param[in]	size	Reprsentation of the position, width and height of the TextInput
 * \param[in]	textColor	Color of the text, if NULL is given, colorText will be black
 * \param[in]	textFont	Font for the text
 * \return True on succsess. Esle false.
 * \author Allan POINT
 * \date 05/01/2022
 */
bool initTextInput(TextInput* textInput, const SDL_Rect* size, const SDL_Color* textColor, TTF_Font* textFont);

/*
 * \brief Free what is needed to be free and clear all data in the TextInput
 * \param[out]	textInput	TextInput to clean
 * \return True on success. Else false.
 * \author Allan POINT
 * \date 07/01/2022
 * \copyright CECILL
 */
bool destroyTextInput(TextInput* textInput);

#endif
