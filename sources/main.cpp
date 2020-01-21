#include "fractal.h"
#include "complex.h"
#include "display.h"
#include "SDL.h"

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

int main(int argc, char* argv[])
{


	// ------------------------- Paramètres du programme -------------------------



	double			x = -0.75;					// Coordonnée x du centre de la vue
	double			y = 0.;						// Coordonnée y du centre de la vue

	double			graph_size = 3.;			// Taille de la vue (zoom)
	int				iteration_nb = 250;			// Nombre d'intérations de la suite (précision)

	Fractale_type	fractale_type = Mandelbrot;	// Type de fractale (Mandelbrot ou Julia)
	Complex			c = Complex(-0.55, 0.55);	// Valeur de c (pour Julia)



	// ---------------------------------------------------------------------------



	SDL_Init(SDL_INIT_VIDEO);

	window = NULL;
	renderer = NULL;

	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, 0, &window, &renderer);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_ADD);
	SDL_SetWindowTitle(window, "Fractal generator");
	SDL_Event event;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);

	contour();
	show_image(x, y, graph_size, iteration_nb, fractale_type, c, event);

	SDL_RenderPresent(renderer);

	while (1)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(1);
		}
	}

	if (renderer)
		SDL_DestroyRenderer(renderer);

	if (window)
		SDL_DestroyWindow(window);

	SDL_Quit();
	return 0;
}