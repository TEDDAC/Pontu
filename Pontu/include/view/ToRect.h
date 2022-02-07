#ifndef TO_RECT_INCLUDED
#define TO_RECT_INCLUDED

#include <SDL2/SDL_rect.h>
#include "model/Coord.h"

SDL_Rect coordToRect(const SDL_Rect* boardRect, const Coord* coord);


#endif //TO_RECT_INCLUDED
