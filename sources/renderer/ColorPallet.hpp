#ifndef COLOR_PALLET_HPP
#define COLOR_PALLET_HPP

#include "libraries.hpp"

class ColorPallet
{
public:

	static std::vector<std::vector<dim::Color>> pallets;
	static constexpr int rgb = 5;
	static constexpr int black_or_white = 7;
	static bool menu(int& index);
};

#endif
