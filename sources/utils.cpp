#include "utils.h"
#include "simulation.h"

int screen_width;

// Construit un gestionnaire d'événement

My_event::My_event()
{
	sf_event = NULL;
	window = NULL;
	end = NULL;
	wheel_move = NULL;
	simulation = NULL;
}

// Construit un gestionnaire d'événement à partir d'un autre

My_event::My_event(const My_event& sf)
{
	*this = sf;
}

// Construit un gestionnaire d'événement à partir des pointeurs qu'il utilise

My_event::My_event(sf::Event* sf_event, sf::RenderWindow* window, bool* end, int16_t* whell_move, Simulation* simulation)
{
	this->sf_event = sf_event;
	this->window = window;
	this->end = end;
	this->wheel_move = whell_move;
	this->simulation = simulation;
}

// Assignation

void My_event::operator=(const My_event& sf)
{
	sf_event = sf.sf_event;
	window = sf.window;
	end = sf.end;
	wheel_move = sf.wheel_move;
	simulation = sf.simulation;
}

// Gestion des différents types d'événements

bool My_event::events()
{
	switch ((*sf_event).type)
	{
	case sf::Event::Closed:
		(*window).close();
		*end = true;
		return false;

	case sf::Event::MouseWheelMoved:
		*wheel_move += (*sf_event).mouseWheel.delta;
		(*simulation).change = true;
		return false;

	case sf::Event::MouseButtonReleased:
		if ((*sf_event).mouseButton.button == sf::Mouse::Left && (*simulation).fractal_type == JULIA)
			(*simulation).example_index = ((*simulation).example_index == 0 ? (*simulation).julia_examples.size() - 1 : (*simulation).example_index - 1);

		else if ((*sf_event).mouseButton.button == sf::Mouse::Right && (*simulation).fractal_type == JULIA)
			(*simulation).example_index = ((*simulation).example_index == (*simulation).julia_examples.size() - 1 ? 0 : (*simulation).example_index + 1);

		else if ((*sf_event).mouseButton.button == sf::Mouse::Middle)
			(*simulation).fractal_type = ((*simulation).fractal_type == MANDELBROT ? JULIA : MANDELBROT);

		else
			break;

		(*simulation).change = true;
		return false;
	}

	return true;
}

// Vérifie si un événement se produit

bool My_event::check()
{
	while ((*window).pollEvent(*sf_event))
		if (!events())
			return false;

	return true;
}

// Attend qu'un événement se produit

bool My_event::wait()
{
	(*window).waitEvent(*sf_event);

	return events();
}

// Donne un entier entre min et max

int random_int(int min, int max)
{
	return rand() % (max - min) + min;
}

// Donne "vrai" avec une probabilité choisie

bool rand_probability(const double& probability)
{
	if (probability < 0.)
		return false;

	if (probability < 1.)
		return ((double)rand() / (double)RAND_MAX < probability);

	return true;
}

// Convertit une couleur HSV en RGB

sf::Color HSVtoRGB(float H, float S, float V)
{
	float s = S / 100.;
	float v = V / 100.;
	float C = s * v;
	float X = C * (1. - abs(fmod(H / 60., 2.) - 1.));
	float m = v - C;
	float r, g, b;

	if (H >= 0 && H < 60)
		r = C, g = X, b = 0;

	else if (H >= 60 && H < 120)
		r = X, g = C, b = 0;

	else if (H >= 120 && H < 180)
		r = 0, g = C, b = X;

	else if (H >= 180 && H < 240)
		r = 0, g = X, b = C;

	else if (H >= 240 && H < 300)
		r = X, g = 0, b = C;

	else
		r = C, g = 0, b = X;

	return sf::Color((r + m) * 255, (g + m) * 255, (b + m) * 255, 255);
}