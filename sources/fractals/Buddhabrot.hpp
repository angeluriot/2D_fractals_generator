#ifndef BUDDHABROT_HPP
#define BUDDHABROT_HPP

#include "fractals/Fractal.hpp"

class Buddhabrot : public Fractal
{
public:

	int max_iterations;
	int nb_points;

	Buddhabrot();
	Buddhabrot(const Buddhabrot& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif