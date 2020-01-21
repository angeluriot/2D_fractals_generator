#ifndef DISPLAY_H
#define DISPLAY_H
#include <windows.h>
#include "SDL.h"

extern SDL_Renderer* renderer;

void set_point(const int& x, const int& y, const COLORREF& color, const int& window_size);
COLORREF color(int value, const int& max_value, const double& color_constant);

#endif