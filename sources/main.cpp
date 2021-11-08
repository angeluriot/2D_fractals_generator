#include <dim/dimension3D.hpp>
#include "Simulator.hpp"

int main()
{
	dim::Window::open("2D fractals generator", 0.75f, "resources/icons/icon.png");
	dim::Window::get_window().setFramerateLimit(60);
	Simulator::init();

	while (dim::Window::running)
	{
		// Check the events.
		sf::Event sf_event;
		while (dim::Window::poll_event(sf_event))
		{
			dim::Window::check_events(sf_event);
			Menu::check_events(sf_event);
			Simulator::check_events(sf_event);
		}

		dim::Window::clear(dim::Color::black);
		dim::Window::update();

		Simulator::update();
		Simulator::draw();

		Menu::display();
		dim::Window::display();
	}

	dim::Window::close();
	return EXIT_SUCCESS;
}
