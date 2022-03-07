#include "engine/InputProcessor.h"

InputProcessor createInputProcessor() {
	InputProcessor inputProcessor = {
		.tabButton = array_P_Button_Create(),
		.tabTextInput = array_TextInput_Create(),
		.selectedTextInput = NULL
	};
	SDL_StopTextInput();
	return inputProcessor;
}

void freeInputProcessor(InputProcessor* inputProcessor) {
	array_P_Button_Free(&inputProcessor->tabButton);
}

InputElement proccessInput(InputProcessor *inputProcessor)
{
	SDL_Event event;
	if (!SDL_PollEvent(&event))
	{
		return createInputElementNone();
	}

	switch (event.type)
	{
		case SDL_QUIT:
			return createInputElementUIQuit();
		case SDL_MOUSEBUTTONUP:
		{
			const SDL_Point mousePoint = {.x = event.button.x, .y = event.button.y};

			for (size_t i = 0; i<inputProcessor->tabButton.size; ++i) {
				P_Button* b = &inputProcessor->tabButton.elems[i];
				if (isHover(b)) {
					b->onClick(b);
                                	break; 
				}
			}
			bool textInputClicked = false;
			for (size_t i = 0; i<inputProcessor->tabTextInput.size; ++i) {
				TextInput* ti = &inputProcessor->tabTextInput.elems[i];
				if (SDL_PointInRect(&mousePoint, &ti->size)) {
					if (inputProcessor->selectedTextInput == NULL) {
						SDL_StartTextInput();
					}
					else {
						inputProcessor->selectedTextInput->isActive = false;
					}
					inputProcessor->selectedTextInput = ti;
					textInputClicked = true;
					inputProcessor->selectedTextInput->isActive = true;
					inputProcessor->selectedTextInput->cursorPosition = strlen(inputProcessor->selectedTextInput->value);
					break;
				}
			}
			if (!textInputClicked && inputProcessor->selectedTextInput != NULL) {
				inputProcessor->selectedTextInput->isActive = false;
				inputProcessor->selectedTextInput = NULL;

				SDL_StopTextInput();
			}
			return createInputElementNone();
		}
		case SDL_MOUSEMOTION:
		{
			for (size_t i = 0; i<inputProcessor->tabButton.size; ++i) {
				P_Button* b = &inputProcessor->tabButton.elems[i];
				int res = isButtonInteractWithCursor(b, event.motion.x, event.motion.y);
				if (res != BUTTON_NOTHING) {
					return createInputElementButtonClicked(b, res);
				}
			}
			break;
		}
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				return createInputElementResizeWindow(event.window.data1, event.window.data2);
			}
			if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
				return createInputElementCloseWindow();
			}
			break;
		case SDL_TEXTINPUT:
			addStringToInputTextValue(inputProcessor->selectedTextInput, event.text.text);
			return createInputElementTextInput(inputProcessor->selectedTextInput);
			break;
		case SDL_TEXTEDITING:
			inputProcessor->selectedTextInput->cursorPosition = event.edit.start;
			return createInputElementTextInput(inputProcessor->selectedTextInput);
			break;
		case SDL_KEYDOWN:
			if (inputProcessor->selectedTextInput != NULL && event.key.keysym.sym == SDLK_BACKSPACE) {
				removeCharacterToInputTextValueAtCursor(inputProcessor->selectedTextInput);
				return createInputElementTextInput(inputProcessor->selectedTextInput);
			}
			break;
	}

	return createInputElementNone();
}
