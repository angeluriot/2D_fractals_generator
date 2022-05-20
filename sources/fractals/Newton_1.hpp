#ifndef NEWTON_1_HPP
#define NEWTON_1_HPP

#include "fractals/Fractal.hpp"

class Newton_1 : public Fractal
{
public:

	std::array<float, 2>	p_1;
	std::array<float, 2>	p_2;
	std::array<float, 2>	p_3;
	bool					smooth;

	Newton_1();
	Newton_1(const Newton_1& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;
	void compute() override;
};

#endif
