#include "InputProcessor.h"

struct p_coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect){
	struct p_coord coord = {
		coord.x = (point->x-boardRect->x)*9/boardRect->w;
		coord.x = (point->y-boardRect->y)*9/boardRect->h;
	}
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
			inputProcessor->selectedCase = screenCoordToGameCoord(&mousePoint);
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
			if (coordValide(inputProcessor->selectedCase))
			{
				struct p_coord newCoord = screenCoordToGameCoord(&mousePoint);
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
				if (SDL_PointInRect(&mousePoint, &inputProcessor->tabButton.button[i].rect)) {

				}
			}
		}
	}
	}
}

