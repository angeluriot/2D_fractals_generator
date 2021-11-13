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
		Julia		= 0,	// A unique galaxy.
		Mandelbrot	= 1,	// Two galaxies colliding.
		Universe	= 2		// The big bang.
	};

	static Image image;

	virtual Type get_type() const = 0;
	virtual void menu() = 0;
	virtual void reset() = 0;
	virtual void compute() = 0;
};

#endif
