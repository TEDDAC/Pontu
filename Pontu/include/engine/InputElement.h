/**
 * \file InputElement.h
 * \brief Define a structure and facilities for input elements
 * \author Martin Rouault
 * \date 06/12/2021
 */

#ifndef INPUT_ELEMENT_INCLUDED
#define INPUT_ELEMENT_INCLUDED


#include "model/Coord.h"
#include "engine/Button.h"
#include "engine/TextInput.h"


/**
 * \enum InputType
 * \brief Different types for input
*/
typedef enum {InputType_None, InputType_ClickGame, InputType_MoveGame, InputType_ActivateUI,  InputType_Window_Resize, InputType_Window_Close, InputType_ButtonChanged, InputType_TextInput} InputType;

/**
 * \enum UIAction
 * \brief Les differentes actions accessible via l'interface utilisateur
*/
typedef enum {UIAction_Validate, UIAction_Cancel, UIAction_Quit } UIAction;

/**
 * \struct InputElement
 * \brief Represent a input element
 */
typedef struct {
    /**
     * \union data
     * \brief Either a coord, a starting and ending coords, or an action for general UI
    */
    union data
    {
        Coord coord; ///< Coordinate for simple click on the board

        struct move {
            Coord start;
            Coord end;
        } move; ///< Pair of coordinates for move on the board

        UIAction uiAction; ///< L'action

		struct windowSize {
			int w;
			int h;
		} windowSize; ///< La nouvelle taille de l'ecran

        struct buttonEvent {
            P_Button* button;
            ButtonEvent event;
        } buttonEvent;

        TextInput* textInput;

    } data; ///< Informations about the input

    InputType type; ///< Type of input
} InputElement;

/**
 * \brief Create a none input element
 * \return A none input element
*/
InputElement createInputElementNone();

/**
 * \brief Create a quit input element
 * \return A quit input element
*/
InputElement createInputElementUIQuit();

/**
 * \brief Create a click on board input element
 * \param [in] newCoord The board's square which is clicked
 * \return A click on board input element
*/
InputElement createInputElementClickBoard(const Coord newCoord);

/**
 * \brief Create a move on board input element
 * \param [in] start The board's square where the movement starts
 * \param [in] end The board's square where the movement ends
 * \return A move on board input element
*/
InputElement createInputElementMoveBoard(const Coord start, const Coord end);

/**
 * @brief Create a Input Element Resize Window
 *
 * @return InputElement InputType_Window_Resize
 */
InputElement createInputElementResizeWindow();

InputElement createInputElementCloseWindow();


InputElement createInputElementButtonClicked(P_Button* button, const ButtonEvent event);

InputElement createInputElementTextInput(TextInput* textInput);

#endif // INPUT_ELEMENT_INCLUDED
