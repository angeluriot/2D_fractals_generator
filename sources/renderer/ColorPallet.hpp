#ifndef COLOR_PALLET_HPP
#define COLOR_PALLET_HPP

#include "libraries.hpp"

class ColorPallet
{
public:

	static std::vector<std::vector<dim::Color>> pallets;	// The list of color pallets.
	static constexpr int rgb = 5;							// The id of the RGB pallet.
	static constexpr int black_or_white = 7;				// The id of the black and white pallet.

	/**
	 * @brief Show the color pallet menu.
	 *
	 * @param index the index of the color pallet
	 * @return true if the selected color pallet changed
	 */
	static bool menu(int& index);
};

#endif
