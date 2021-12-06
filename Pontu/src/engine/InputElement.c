#include "InputElement.h"



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

InputElement createInputElementMoveBoard(const struct p_coord start, const struct p_coord end) {
    InputElement i = {.type=InputType_MoveGame, .data.move={.start=start, .end=end}};
    return i;
}
