/**
 * \file InputElement.h
 * \brief Define a structure and facilities for input elements
 * \author Martin Rouault
 * \date 06/12/2021
 */
#ifndef INPUT_ELEMENT_INCLUDED
#define INPUT_ELEMENT_INCLUDED


#include "Coord.h"

typedef enum {InputType_None, InputType_ClickGame, InputType_MoveGame, InputType_ActivateUI} InputType;
typedef enum {UIAction_Validate, UIAction_Cancel, UIAction_Quit } UIAction;

/**
 * \struct InputElement 
 * \brief Represent a input element 
 */
typedef struct {
    union
    {
        struct p_coord coord; ///< Coordinate for simple click on the board

        struct {
            struct p_coord start;
            struct p_coord end;
        } move; ///< Pair of coordinates for move on the board
        
        UIAction uiAction;
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
InputElement createInputElementClickBoard(const struct p_coord newCoord);
InputElement createInputElementMoveBoard(const struct p_coord start, const struct p_coord end);

#endif // INPUT_ELEMENT_INCLUDED
