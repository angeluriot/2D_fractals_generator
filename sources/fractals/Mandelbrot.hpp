#ifndef MANDELBROT_HPP
#define MANDELBROT_HPP

#include "fractals/Fractal.hpp"

class Mandelbrot : public Fractal
{
public:

	int		pallet_index;
	float	color_range;
	float	color_shift;
	bool	smooth;

	Mandelbrot();
	Mandelbrot(const Mandelbrot& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif
