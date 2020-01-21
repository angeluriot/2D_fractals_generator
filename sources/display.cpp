#include "display.h"
#include "SDL.h"



// Affiche un pixel aux coordonnées voulues

void set_point(const int& x, const int& y, const COLORREF& color)
{
	SDL_SetRenderDrawColor(renderer, GetRValue(color), GetGValue(color), GetBValue(color), SDL_ALPHA_OPAQUE);
	SDL_RenderDrawPoint(renderer, GAP_X + x, GAP_Y + DISPLAY_SIZE - y);
}



// Donne une couleur à partir du temps que prend la suite à diverger

COLORREF color(int value, const int& max_value)
{
	value *= COLOR_CONSTANT;

	value = int(double((double(value) / double(max_value)) * double(255. * 2.)));

	if (value <= 255)
		return RGB(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return RGB(2 * 255 - value, 0, value - 255);

	return RGB(0, 0, 0);
}



// Trace un contour blanc

void contour()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for (int i = 0; i < DISPLAY_SIZE; i++)
	{
		SDL_RenderDrawPoint(renderer, i + GAP_X, GAP_Y);
		SDL_RenderDrawPoint(renderer, i + GAP_X, GAP_Y + DISPLAY_SIZE + 1);
	}

	for (int j = 0; j < DISPLAY_SIZE + 2; j++)
	{
		SDL_RenderDrawPoint(renderer, GAP_X - 1, j + GAP_Y);
		SDL_RenderDrawPoint(renderer, GAP_X + DISPLAY_SIZE, j + GAP_Y);
	}
}