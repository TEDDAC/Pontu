#include "engine/InputProcessor.h"

Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect){
	Coord coord = {
		coord.x = (point->x-boardRect->x)*9/boardRect->w,
		coord.y = (point->y-boardRect->y)*9/boardRect->h
	};
	return coord;
}


InputElement proccessInput(InputProcessor *inputProcessor, const SDL_Rect* boardRect)
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
		if (SDL_PointInRect(&mousePoint, boardRect))
		{
			inputProcessor->selectedCase = screenCoordToGameCoord(&mousePoint, boardRect);
		}
		else
		{
		}
		break;
	}
	case SDL_MOUSEBUTTONUP:
	{
		const SDL_Point mousePoint = {.x = event.button.x, .y = event.button.y};
		if (SDL_PointInRect(&mousePoint, boardRect))
		{
			if (coordValid(inputProcessor->selectedCase))
			{
				Coord newCoord = screenCoordToGameCoord(&mousePoint, boardRect);
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
			/*for (size_t i = 0; i<inputProcessor->tabButton.size; ++i) {
				if (SDL_PointInRect(&mousePoint, &inputProcessor->tabButton.buttons[i].rect)) {
					// ...
				}
			}*/
			return createInputElementNone();
		}
		break;
		}
	}

	return createInputElementNone();
}

