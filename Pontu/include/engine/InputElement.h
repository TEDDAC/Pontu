#ifndef INPUT_ELEMENT_INCLUDED
#define INPUT_ELEMENT_INCLUDED

/*
Clique sur un element (param coord du jeu)
Deplace Element (params coord du jeu debut et fin)

Clique sur element UI
Fleche pour selectionner element UI
Entré -> active element UI
*/

#include "Coord.h"

typedef enum {InputType_None, InputType_ClickGame, InputType_MoveGame, InputType_ActivateUI} InputType;
typedef enum {UIAction_Validate, UIAction_Cancel, UIAction_Quit } UIAction;

typedef struct {
    union
    {
        struct p_coord coord;

        struct {
            struct p_coord start;
            struct p_coord end;
        } move;
        
        UIAction uiAction;
    } data;
    
    InputType type;
} InputElement;


InputElement createInputElementNone() {
    InputElement i = {.type=InputType_None};
    return i;
}

InputElement createInputElementUIQuit() {
    InputElement i = {.type=InputType_ActivateUI, .data.uiAction=UIAction_Quit};
    return i;
}

InputElement createInputElementClickBoard(const struct p_coord newCoord) {
    InputElement i = {.type=InputType_ClickGame, .data.coord = newCoord};
    return i;
}

InputElement createInputElementMoveBoard(const struct p_coord newCoord) {
    InputElement i = {.type=InputType_MoveGame, .data.coord = newCoord};
    return i;
}


#endif // INPUT_ELEMENT_INCLUDED
