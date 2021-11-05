#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "libraries.hpp"
#include "Menu.hpp"

/**
 * @brief Takes care of the simulation display.
 */
class Renderer
{
public:

	static dim::VertexBuffer screen;

	/**
	 * @brief Initialize the renderer.
	 */
	static void init();

	static void change_type();

	/**
	 * @brief Check the events of the renderer.
	 *
	 * @param sf_event the SFML event object
	 */
	static void check_events(const sf::Event& sf_event);

	/**
	 * @brief Clear the FBOs.
	 */
	static void clear();

	/**
	 * @brief Draw the simulation.
	 */
	static void draw();
};

#endif
