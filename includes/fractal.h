#ifndef FRACTAL_H
#define FRACTAL_H
#include "complex.h"
#include "SDL.h"

enum Fractale_type { Julia, Mandelbrot }; // Type de fractale

int sequence(Complex z, const Complex& c, const int& iteration_nb, const double& sequences_max);
void show_image(const double& p_x, const double& p_y, const double& graph_size, const int& iteration_nb, const Fractale_type& fractale_type, const Complex& c, SDL_Event& event, const int& window_size, const double& color_constant, const double& sequences_max);

#endif