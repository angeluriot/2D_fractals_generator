#include "display.h"
#include "SDL.h"



// Affiche un pixel aux coordonnées voulues

void set_point(const int& x, const int& y, const COLORREF& color, const int& window_size)
{
	SDL_SetRenderDrawColor(renderer, GetRValue(color), GetGValue(color), GetBValue(color), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, x, window_size - y);
}



// Donne une couleur à partir du temps que prend la suite à diverger

COLORREF color(int value, const int& max_value, const double& color_constant)
{
	value *= color_constant;

	value = int(double((double(value) / double(max_value)) * double(255. * 2.)));

	if (value <= 255)
		return RGB(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return RGB(2 * 255 - value, 0, value - 255);

	return RGB(0, 0, 0);
}