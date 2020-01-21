#include "fractal.h"
#include "complex.h"
#include "display.h"
#include "SDL.h"



// Calcul la suite d'équation z = z² + c et renvoie le nombre d'itérations pour atteindre "sequence_max"

int sequence(Complex z, const Complex& c, const int& iteration_nb, const double& sequences_max)
{
	for (int i = 0; i < iteration_nb; i++)
	{
		z = z * z + c; // L'équation

		if (z.modulus() > sequences_max)
			return i;
	}

	return iteration_nb;
}



// Affiche l'image en entier de la forme fractale

void show_image(const double& p_x, const double& p_y, const double& graph_size, const int& iteration_nb, const Fractale_type& fractale_type, const Complex& c, SDL_Event& event, const int& window_size, const double& color_constant, const double& sequences_max)
{
	double x = p_x - graph_size / 2.;
	double y = p_y - graph_size / 2.;
	double x_pas = graph_size / double(window_size);
	double y_pas = graph_size / double(window_size);

	for (int i = 0; i < window_size; i++)
	{
		x = p_x - graph_size / 2;
		y += y_pas;

		for (int j = 0; j < window_size; j++)
		{
			x += x_pas;

			int sequence_result;

			if (fractale_type == Julia)
			{
				Complex z = Complex(x, y);
				sequence_result = sequence(z, c, iteration_nb, sequences_max);
			}

			else
			{
				Complex c = Complex(x, y);
				sequence_result = sequence(Complex(0, 0), c, iteration_nb, sequences_max);
			}

			if (sequence_result != iteration_nb)
				set_point(j, i, color(sequence_result, iteration_nb, color_constant), window_size);
		}

		SDL_RenderPresent(renderer);

		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
		{
			SDL_Quit();
			exit(1);
		}
	}
}