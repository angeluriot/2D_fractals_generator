#ifndef DISPLAY_H
#define DISPLAY_H
#include <windows.h>
#include "SDL.h"

#define HEIGHT			1080	// Hauteur de la fen�tre (en pixels)
#define WIDTH			1920	// Largeur de la fen�tre (en pixels)
#define DISPLAY_SIZE	800		// Taille de l'affichage (en pixels)
#define GAP_X			200		// D�calage en X (en pixels)
#define GAP_Y			100		// D�calage en Y (en pixels)
#define COLOR_CONSTANT	7.		// Constante permettant d'am�liorer les couleurs
#define SEQUENCE_MAX	10.		// Le calcul de la suite s'arr�te quand elle atteint cette valeur

extern SDL_Renderer* renderer;

void set_point(const int& x, const int& y, const COLORREF& color);
COLORREF color(int value, const int& max_value);
void contour();

#endif