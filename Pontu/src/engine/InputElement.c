#include "engine/InputElement.h"



InputElement createInputElementNone() {
    InputElement i = {.type=InputType_None};
    return i;
}


InputElement createInputElementUIQuit() {
    InputElement i = {.type=InputType_ActivateUI, .data.uiAction=UIAction_Quit};
    return i;
}

InputElement createInputElementClickBoard(const Coord newCoord) {
    InputElement i = {.type=InputType_ClickGame, .data.coord = newCoord};
    return i;
}

InputElement createInputElementMoveBoard(const Coord start, const Coord end) {
    InputElement i = {.type=InputType_MoveGame, .data.move={.start=start, .end=end}};
    return i;
}
