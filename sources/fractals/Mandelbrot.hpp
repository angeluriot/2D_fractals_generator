#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include "fractals/Fractal.hpp"

class Mandelbrot : public Fractal
{
public:

	int max_iterations;

	Mandelbrot();
	Mandelbrot(const Mandelbrot& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void render() override;
};

#endif
