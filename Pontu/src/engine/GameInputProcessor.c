#include "engine/GameInputProcessor.h"

Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect){
	Coord coord = {
		coord.x = (point->x-boardRect->x)*9/boardRect->w,
		coord.y = (point->y-boardRect->y)*9/boardRect->h
	};
	return coord;
}

GameInputProcessor createGameInputProcessor() {
	GameInputProcessor gameInputProcessor = {
		.selectedCase = {.x=-1, .y=-1},
		.tabButton = array_P_Button_Create()
	};
	return gameInputProcessor;
}

void freeGameInputProcessor(GameInputProcessor* gameInputProcessor) {
	array_P_Button_Free(&gameInputProcessor->tabButton);
}

InputElement proccessGameInput(GameInputProcessor *gameInputProcessor, const SDL_Rect* boardRect)
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
				if (!coordValid(gameInputProcessor->selectedCase)) {
					gameInputProcessor->selectedCase = screenCoordToGameCoord(&mousePoint, boardRect);
				}
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
				if (coordValid(gameInputProcessor->selectedCase))
				{
					Coord newCoords = screenCoordToGameCoord(&mousePoint, boardRect);
					if (coordEqual(gameInputProcessor->selectedCase, newCoords)) {
						gameInputProcessor->selectedCase = newCoords;
						return createInputElementClickBoard(newCoords);
					}
					else {
						const Coord oldCoord = gameInputProcessor->selectedCase;
						gameInputProcessor->selectedCase = newCoord(-1,-1);
						return createInputElementMoveBoard(oldCoord, newCoords);
					}
				}
			}
			else
			{
				for (size_t i = 0; i<gameInputProcessor->tabButton.size; ++i) {
					P_Button* b = &gameInputProcessor->tabButton.elems[i];
					if (SDL_PointInRect(&mousePoint, &b->rect)) {
						b->onClick(b);
					}
				}
				return createInputElementNone();
			}
			break;
		}
		case SDL_MOUSEMOTION:
		{
			for (size_t i = 0; i<gameInputProcessor->tabButton.size; ++i) {
				P_Button* b = &gameInputProcessor->tabButton.elems[i];
				isButtonEntry(b, event.motion.x, event.motion.y);
			}
			break;
		}
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				return createInputElementResizeWindow(event.window.data1, event.window.data2);
			}
			break;
	}

	return createInputElementNone();
}
