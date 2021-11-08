#ifndef FRACTAL_HPP
#define FRACTAL_HPP

#include "libraries.hpp"

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

	static dim::Mesh mesh;

	virtual Type get_type() const = 0;
	virtual void menu() = 0;
	virtual void reset() = 0;
	virtual void render() = 0;
};

#endif
