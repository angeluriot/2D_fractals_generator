#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "menu/Menu.hpp"
#include "renderer/Renderer.hpp"
#include "fractals/Fractal.hpp"
#include "fractals/Julia.hpp"
#include "fractals/Mandelbrot.hpp"
#include "fractals/BurningShip.hpp"
#include "fractals/Buddhabrot.hpp"
#include "fractals/Newton_1.hpp"
#include "fractals/Newton_2.hpp"
#include "compute_shader/ComputeShader.hpp"
#include "compute_shader/Image.hpp"
#include "renderer/ColorPallet.hpp"

/**
 * @brief A static class representing the simulation.
 */
class Simulator
{
public:

	static Fractal*					fractal;		// The fractal to compute.
	static double					area_width;		// The width of the area on the screen.
	static std::array<double, 2>	position;		// The center of the area on the screen.
	static bool						moving_point;	// True if the user is moving a Newton's point.
	static bool						image_done;		// True if the image is computed.

	/**
	 * @brief Initialize the simulation.
	 */
	static void init();

	/**
	 * @brief Reset the simulation
	 */
	static void reset();

	/**
	 * @brief Transform a screen position to a fractal position.
	 *
	 * @param position the screen position
	 * @return the fractal position
	 */
	static std::array<double, 2> screen_to_world(dim::Vector2int position);

	/**
	 * @brief Transform a fractal position to a screen position.
	 *
	 * @param position the fractal position
	 * @return the screen position
	 */
	static dim::Vector2int world_to_screen(std::array<double, 2> position);

	/**
	 * @brief Handle the events of the simulation.
	 */
	static void update();

	/**
	 * @brief Check the simulation events.
	 *
	 * @param sf_event the SFML event object
	 */
	static void check_events(const sf::Event& sf_event);

	/**
	 * @brief Draw the simulation.
	 */
	static void draw();
};

#endif
