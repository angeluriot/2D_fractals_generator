#ifndef BUDDHABROT_HPP
#define BUDDHABROT_HPP

#include "fractals/Fractal.hpp"

class Buddhabrot : public Fractal
{
public:

	int		nb_points;	// The number of points to compute.
	float	brightness;	// The brightness of the image.

	Buddhabrot();
	Buddhabrot(const Buddhabrot& other) = default;

	Type get_type() const override;
	void menu() override;
	void reset() override;

	/**
	 * @brief Compute the Buddhabrot fractal for a specific clor.
	 *
	 * @param points_buffer a buffer containing the points to compute
	 * @param color_id the color id of the points to compute
	 * @param current_max_iterations the current max iterations number
	 */
	void compute_color(const cl::Buffer& points_buffer, int color_id, int current_max_iterations);

	void compute() override;
};

#endif
