#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include "Menu.hpp"
#include "Renderer.hpp"

/**
 * @brief A static class representing the simulation.
 */
class Simulator
{
public:

	/**
	 * @brief Initialize the simulation.
	 */
	static void init();

	/**
	 * @brief Update the simulation.
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
