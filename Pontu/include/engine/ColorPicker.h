#ifndef COLOR_PICKER_INCLUDED
#define COLOR_PICKER_INCLUDED

#include <SDL2/SDL.h>
#include "engine/Button.h"

typedef struct
{
  P_Button colorButtons[4];
  SDL_Color selectedColor;
}ColorPicker;

void drawColorPicker(SDL_Renderer* renderer, ColorPicker cp);

#endif // COLOR_PICKER_INCLUDED
