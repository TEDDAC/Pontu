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

InputElement createInputElementResizeWindow(const int w, const int h) {
	InputElement i = {
		.type = InputType_Window_Resize,
		.data.windowSize={.w = w, .h = h}
	};
	return i;
}

InputElement createInputElementButtonChanged(P_Button* button, const ButtonEvent event) {
    InputElement i = {
		.type = InputType_ButtonChanged,
		.data.buttonEvent={.event=event, .button = button}
	};
	return i;
}


InputElement createInputElementTextInput(TextInput* textInput) {
    InputElement i = {
        .type = InputType_TextInput,
		.data.textInput=textInput
	};
	return i;
}

InputElement createInputElementCloseWindow(){
    InputElement i = {.type = InputType_Window_Close};
    return i;
}
