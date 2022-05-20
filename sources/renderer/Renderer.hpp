#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "libraries.hpp"
#include "menu/Menu.hpp"

/**
 * @brief Takes care of the simulation display.
 */
class Renderer
{
public:

	static dim::VertexBuffer screen; // The screen buffer.

	/**
	 * @brief Initialize the renderer.
	 */
	static void init();

	/**
	 * @brief Draw the simulation.
	 */
	static void draw();
};

#endif
