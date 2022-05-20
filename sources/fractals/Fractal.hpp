#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include "libraries.hpp"
#include "compute_shader/Image.hpp"

class Fractal
{
public:

	/**
	 * @brief The type of the fractal
	 */
	enum class Type : int
	{
		Julia		= 0,
		Mandelbrot	= 1,
		BurningShip	= 2,
		Buddhabrot	= 3,
		Newton_1	= 4,
		Newton_2	= 5
	};

	static Image image;	// The image of the fractal.

	int max_iterations; // The max iterations number.

	/**
	 * @brief Give the type of the fractal.
	 *
	 * @return the type of the fractal
	 */
	virtual Type get_type() const = 0;

	/**
	 * @brief Show the menu of the fractal.
	 */
	virtual void menu() = 0;

	/**
	 * @brief Reset the fractal settings.
	 */
	virtual void reset() = 0;

	/**
	 * @brief Compute the fractal image.
	 */
	virtual void compute() = 0;
};

#endif
