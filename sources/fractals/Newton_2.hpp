#ifndef NEWTON_2_HPP
#define NEWTON_2_HPP

#include "fractals/Fractal.hpp"

class Newton_2 : public Fractal
{
public:

	bool					smooth;

	Newton_2();
	Newton_2(const Newton_2& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif
