#ifndef JULIA_HPP
#define JULIA_HPP

#include "fractals/Fractal.hpp"

class Julia : public Fractal
{
public:

	std::array<float, 2>	c;
	int						pallet_index;
	float					color_range;
	float					color_shift;
	bool					smooth;

	Julia();
	Julia(const Julia& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif
