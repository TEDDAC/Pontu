#include "engine/GameInputProcessor.h"

Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect)
{
	Coord coord = { coord.x = (point->x - boardRect->x) * 9 / boardRect->w,
					coord.y = (point->y - boardRect->y) * 9 / boardRect->h };
	return coord;
}

GameInputProcessor createGameInputProcessor()
{
	GameInputProcessor gameInputProcessor = { .selectedCase	  = { .x = -1, .y = -1 },
											  .inputProcessor = createInputProcessor() };
	return gameInputProcessor;
}

void freeGameInputProcessor(GameInputProcessor* gameInputProcessor)
{
	freeInputProcessor(&gameInputProcessor->inputProcessor);
}

InputElement interpretSDL_EventGameInput(GameInputProcessor* gameInputProcessor,
										 const SDL_Rect* boardRect,
										 const SDL_Event* event)
{
	switch (event->type)
	{
		case SDL_MOUSEBUTTONDOWN:
		{
			const SDL_Point mousePoint = { .x = event->button.x, .y = event->button.y };
			if (SDL_PointInRect(&mousePoint, boardRect))
			{
				if (!coordValid(gameInputProcessor->selectedCase))
				{
					gameInputProcessor->selectedCase = screenCoordToGameCoord(&mousePoint, boardRect);
				}
			}
			break;
		}
		case SDL_MOUSEBUTTONUP:
		{
			const SDL_Point mousePoint = { .x = event->button.x, .y = event->button.y };
			if (SDL_PointInRect(&mousePoint, boardRect))
			{
				if (coordValid(gameInputProcessor->selectedCase))
				{
					Coord newCoords = screenCoordToGameCoord(&mousePoint, boardRect);
					if (coordEqual(gameInputProcessor->selectedCase, newCoords))
					{
						gameInputProcessor->selectedCase = newCoords;
						return createInputElementClickBoard(newCoords);
					}
					else
					{
						const Coord oldCoord			 = gameInputProcessor->selectedCase;
						gameInputProcessor->selectedCase = newCoord(-1, -1);
						return createInputElementMoveBoard(oldCoord, newCoords);
					}
				}
			}
			break;
		}
	}

	return createInputElementNone();
}

InputElement proccessGameInput(GameInputProcessor* gameInputProcessor, const SDL_Rect* boardRect)
{
	SDL_Event event;
	if (!SDL_PollEvent(&event))
	{
		return createInputElementNone();
	}

	InputElement ret = interpretSDL_EventGameInput(gameInputProcessor, boardRect, &event);
	if (ret.type == InputType_None)
	{
		return interpretSDL_EventInput(&gameInputProcessor->inputProcessor, &event);
	}
	return ret;
}
