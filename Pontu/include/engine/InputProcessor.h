#ifndef INPUT_PROCESSOR_INCLUDED
#define INPUT_PROCESSOR_INCLUDED

#include "Button.h"
#include "Coord.h"
#include "InputElement.h"

typedef struct
{
	ArrayButton tabButton;
	struct p_coord selectedCase; ///< Board , (-1;-1) si inexistant
} InputProcessor;

InputElement proccessInput(InputProcessor *inputProcessor, const SDL_Rect boardRect)
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
	case SDL_MOUSEBUTTONDOWN:
	{
		const SDL_Point mousePoint = {.x = event.button.x, .y = event.button.y};
		if (SDL_PointInRect(&mousePoint, &boardRect))
		{
			inputProcessor->selectedCase = screenCoordToGameCoord(mousePoint);
		}
		else
		{
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		const SDL_Point mousePoint = {.x = event.button.x, .y = event.button.y};
		if (SDL_PointInRect(&mousePoint, &boardRect))
		{
			if (coordValide(inputProcessor->selectedCase))
			{
				struct p_coord newCoord = screenCoordToGameCoord(mousePoint);
				if (coordEqual(inputProcessor->selectedCase, newCoord)) {
					return createInputElementClickBoard(newCoord);
				}
				else {
					return createInputElementMoveBoard(inputProcessor->selectedCase, newCoord);
				}
				inputProcessor->selectedCase = newCoord;
			}
		}
		else 
		{
			for (size_t i = 0; i<inputProcessor->tabButton.size; ++i) {
				inputProcessor->tabButton.button[i];
			}
		}
	}
	}
}

#endif //INPUT_PROCESSOR_INCLUDED
