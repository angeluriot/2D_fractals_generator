#ifndef BUDDHABROT_HPP
#define BUDDHABROT_HPP

#include "fractals/Fractal.hpp"

class Buddhabrot : public Fractal
{
public:

	int		max_iterations;
	int		nb_points;
	float	brightness;

	Buddhabrot();
	Buddhabrot(const Buddhabrot& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute_color(const cl::Buffer& points_buffer, int color_id, int current_max_iterations);
	void compute() override;
};

#endif
