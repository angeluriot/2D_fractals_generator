#include "simulation.h"

int main()
{
	// Initialisation de la fenêtre en fonction de l'écran

	int width;
	int height;

	if (sf::VideoMode::getDesktopMode().width > (16. / 9.) * sf::VideoMode::getDesktopMode().height)
	{
		height = (sf::VideoMode::getDesktopMode().height * 3) / 4;
		width = (height * 16) / 9;
	}

	else if (sf::VideoMode::getDesktopMode().width < (16. / 9.) * sf::VideoMode::getDesktopMode().height)
	{
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4;
		height = (width * 9) / 16;
	}

	else
	{
		width = (sf::VideoMode::getDesktopMode().width * 3) / 4;
		height = (sf::VideoMode::getDesktopMode().height * 3) / 4;
	}

	screen_width = width;
	
	sf::RenderWindow window(sf::VideoMode(width, height), "Fractal Generator", sf::Style::Close | sf::Style::Titlebar);

	sf::Image icon;
	icon.loadFromFile("dependencies/resources/icon.png");

	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	bool end = false;
	int16_t wheel_move = 0;

	sf::Mouse mouse;
	sf::Cursor cursor;
	sf::Event sf_event;

	cursor.loadFromSystem(sf::Cursor::Cross);
	window.setMouseCursor(cursor);

	Simulation simulation;
	My_event my_event(&sf_event, &window, &end, &wheel_move, &simulation);
	simulation.simulate(my_event);

	// lancement de la simulation

	while (window.isOpen() && !end)
	{
		window.clear(sf::Color::Black);
		
		if (!simulation.change)
			my_event.wait();

		if (simulation.change)
		{
			cursor.loadFromSystem(sf::Cursor::Wait);
			window.setMouseCursor(cursor);

			simulation.update(my_event, mouse);

			cursor.loadFromSystem(sf::Cursor::Cross);
			window.setMouseCursor(cursor);
		}
	}

	return 0;
}