#ifndef JULIA_HPP
#define JULIA_HPP

#include "fractals/Fractal.hpp"

class Julia : public Fractal
{
public:

	dim::Vector2	c;
	int				max_iterations;

	Julia();
	Julia(const Julia& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void render() override;
};

#endif
