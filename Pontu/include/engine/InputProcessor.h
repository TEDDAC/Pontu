#ifndef INPUT_PROCESSOR_INCLUDED
#define INPUT_PROCESSOR_INCLUDED

#include "Button.h"
#include "model/Coord.h"
#include "InputElement.h"

typedef struct
{
	ArrayButton tabButton;
	struct Coord selectedCase; ///< Board , (-1;-1) si inexistant
} InputProcessor;

struct Coord screenCoordToGameCoord(const SDL_Point* point, const SDL_Rect* boardRect);

InputElement proccessInput(InputProcessor *inputProcessor, const SDL_Rect* boardRect);

#endif //INPUT_PROCESSOR_INCLUDED
