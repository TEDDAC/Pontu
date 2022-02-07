#ifndef UI_ELEMENT_UTILS_INCLUDED
#define UI_ELEMENT_UTILS_INCLUDED

#include <SDL2/SDL.h>

typedef enum {
	POSX_LEFT,
	POSX_CENTER,
	POSX_RIGHT
} PositionX_Type;

typedef enum {
	POSY_TOP,
	POSY_CENTER,
	POSY_BOTTOM
} PositionY_Type;

typedef enum {
	ASPECT_KEEP_W, 
	ASPECT_KEEP_H, 
	ASPECT_IGNORE,
	ASPECT_KEEP_FIT
} AspectRatioType;

typedef struct {
	SDL_Rect base100;
	PositionX_Type tpX;
	PositionY_Type tpY;
	AspectRatioType aspectType;
} PositionSpecifier;

PositionSpecifier newPositionSpecifier(const SDL_Rect* const base100, const PositionX_Type tpX, const PositionY_Type tpY, const AspectRatioType aspectType);

SDL_Rect adaptPosToRect(const PositionSpecifier *const positionSpecifier, const SDL_Rect *const globalRect);

#endif //UI_ELEMENT_UTILS_INCLUDED
