#include "view/ToRect.h"

SDL_Rect coordToRect(const SDL_Rect* boardRect, const Coord* coord) {
	const int w = boardRect->w/9;
	const int h = boardRect->h/9;
	SDL_Rect r = {
		.x = boardRect->x + w*coord->x,
		.y = boardRect->y + h*coord->y,
		.w = w,
		.h = h
	};

	return r;
}
