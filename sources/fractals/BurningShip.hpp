#ifndef BURNING_SHIP_HPP
#define BURNING_SHIP_HPP

#include "fractals/Fractal.hpp"

class BurningShip : public Fractal
{
public:

	int		pallet_index;
	float	color_range;
	float	color_shift;
	bool	smooth;

	BurningShip();
	BurningShip(const BurningShip& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif
