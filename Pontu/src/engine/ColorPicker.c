#include "engine/ColorPicker.h"

void drawColorPicker(SDL_Renderer* renderer, ColorPicker cp)
{
  for (int i=0; i<4; ++i) {
    drawButtonOnRenderer(renderer, &cp.colorButtons[i]);
  }
}
