#include "engine/InputProcessor.h"

InputProcessor createInputProcessor() {
	InputProcessor inputProcessor = {
		.tabButton = array_P_Button_Create()
	};
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
				if (SDL_PointInRect(&mousePoint, &b->rect)) {
					b->onClick(b);
				}
			}
			return createInputElementNone();
		}
		case SDL_MOUSEMOTION:
		{
			for (size_t i = 0; i<inputProcessor->tabButton.size; ++i) {
				P_Button* b = &inputProcessor->tabButton.elems[i];
				isButtonEntry(b, event.motion.x, event.motion.y);
			}
			break;
		}
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			return createInputElementResizeWindow(event.window.data1, event.window.data2);
			break;

	}

	return createInputElementNone();
}
