#include "simulation.h"

// Crée une simulation

Simulation::Simulation()
{
	void_image.create(WIDTH, HEIGHT, sf::Color(0, 0, 0, 0));

	thread_nb = std::max((int)std::thread::hardware_concurrency() - FREE_THREAD, 1);

	images.assign(thread_nb, void_image);
	
	finished = std::vector<std::atomic<bool>>(thread_nb);
	std::fill(finished.begin(), finished.end(), false);

	texture.create(WIDTH, HEIGHT);

	fractal_type = MANDELBROT;
	sequence_types = { &Simulation::sequence_mandelbrot, &Simulation::sequence_julia };

	position = Vector(0., 0.);
	zoom = 5.;

	julia_examples = {
		Complex(-0.8, 0.),
		Complex(0.285, 0.01),
		Complex(-0.1, 0.75),
		Complex(-1.476, 0),
		Complex(-0.1, 0.65),
		Complex(0.4, 0.6),
		Complex(-0.95, 0.25),
		Complex(0., -0.8),
		Complex(-0.7, 0.2),
		Complex(-0.70176, 0.3842) };

	example_index = 0;
	change = false;
}

// Donne la position de la souris par rapport au centre à partir de la position SFML de la souris

Vector Simulation::get_position(const sf::Vector2i& position)
{
	return Vector(static_cast<double>(position.x) - static_cast<double>(WIDTH) / 2., static_cast<double>(HEIGHT) / 2. - static_cast<double>(position.y));
}

// Passe des coordonnées de l'écran à celui du graphique

Vector Simulation::window_to_graph(const Vector& position)
{
	return Vector(((position.x / static_cast<double>(WIDTH)) * zoom), ((position.y / static_cast<double>(WIDTH)) * zoom));
}

// Passe des coordonnées du graphique à celui de l'écran

Vector Simulation::graph_to_window(const Vector& position)
{
	return Vector((position.x / zoom) * static_cast<double>(WIDTH), (position.y / zoom) * static_cast<double>(WIDTH));
}

// Calcul la suite d'équation z = z² + c et renvoie le nombre d'itérations pour atteindre "sequence_max" pour Mandelbrot

uint16_t Simulation::sequence_mandelbrot(Complex c, uint16_t iteration_nb)
{
	Complex z = Complex(0, 0);

	for (uint16_t i = 0; i < iteration_nb; i++)
	{
		z = (z ^ 2) + c;

		if (z.modulus2() > SEQUENCE_MAX2)
			return i;
	}

	return iteration_nb;
}

// Calcul la suite d'équation z = z² + c et renvoie le nombre d'itérations pour atteindre "sequence_max" pour Julia

uint16_t Simulation::sequence_julia(Complex z, uint16_t iteration_nb)
{
	Complex c = julia_examples[example_index];

	for (uint16_t i = 0; i < iteration_nb; i++)
	{
		z = (z ^ 2) + c;

		if (z.modulus2() > SEQUENCE_MAX2)
			return i;
	}

	return iteration_nb;
}

// Génère l'image de la fractale

void Simulation::draw_fractal(uint16_t y_min, uint16_t y_max, uint8_t thread_number)
{
	Vector graph_size(zoom, zoom * (9. / 16.));
	double x = position.x - graph_size.x / 2.;
	double y = position.y + graph_size.y / 2.;
	double step = zoom / static_cast<double>(WIDTH);

	uint16_t iteration_nb = pow(1. / zoom, 0.3) * 250.;
	uint16_t sequence_result;

	for (uint16_t i = y_min; i < y_max; i++)
	{
		x = position.x - graph_size.x / 2;
		y = position.y + graph_size.y / 2. - i * step;

		for (uint16_t j = 0; j < WIDTH; j++)
		{
			x += step;
			sequence_result = (this->*sequence_types[fractal_type])(Complex(x, y), iteration_nb);

			if (sequence_result != iteration_nb)
				images[thread_number].setPixel(j, i, color(sequence_result, iteration_nb));
		}
	}

	if (finished[thread_number])
		return;

	finished[thread_number] = true;
}

// Gère le multi-threading de la fonction draw_factal

void Simulation::simulate(My_event& my_event)
{
	bool image_finished = true;

	images.assign(thread_nb, void_image);

	finished = std::vector<std::atomic<bool>>(thread_nb);
	std::fill(finished.begin(), finished.end(), false);

	std::vector<std::thread> threads(thread_nb);

	for (uint8_t i = 0; i < threads.size(); i++)
		threads[i] = std::thread([this, i]() { draw_fractal((HEIGHT / static_cast<double>(thread_nb)) * i, (HEIGHT / static_cast<double>(thread_nb)) * (i + 1), i); });

	while (!std::all_of(finished.begin(), finished.end(), [](bool i) -> bool { return i; }))
		if (!my_event.check())
		{
			std::fill(finished.begin(), finished.end(), true);
			image_finished = false;
		}

	for (auto& thread : threads)
		thread.join();

	if (image_finished)
		draw(*my_event.window);
}

// Met à jour la simulation

void Simulation::update(My_event& my_event, sf::Mouse& mouse)
{
	if (*my_event.wheel_move != 0)
	{
		int8_t inverted = (*my_event.wheel_move > 0 ? 1 : -1);

		position += inverted * window_to_graph(get_position(mouse.getPosition(*my_event.window)));

		zoom = (*my_event.wheel_move > 0 ? zoom / (1.5 * abs(*my_event.wheel_move)) : zoom * (1.5 * abs(*my_event.wheel_move)));
		*my_event.wheel_move = 0;

		position -= inverted * window_to_graph(get_position(mouse.getPosition(*my_event.window)));
	}

	change = false;
	simulate(my_event);
}

// Donne une couleur à partir du temps que prend la suite à diverger

sf::Color Simulation::color(uint16_t value, uint16_t max_value)
{
	value = (value / static_cast<double>(max_value)) * 1000;

	if (value <= 700)
	{
		if ((value / HSV_DIFF) % 2)
			return HSVtoRGB(value % HSV_DIFF + HSV_MIN, 100, 100);

		return HSVtoRGB(HSV_MAX - (value % HSV_DIFF), 100, 100);
	}

	return sf::Color(0, 0, 0, 255);
}

// Affiche la simulation

void Simulation::draw(sf::RenderWindow& window)
{
	for (auto& image : images)
	{
		texture.update(image);
		sprite.setTexture(texture);
		window.draw(sprite);
	}

	window.display();
}