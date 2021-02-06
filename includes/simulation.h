#ifndef SIMULATION_H
#define SIMULATION_H
#include "utils.h"
#include "complex.h"

// Classe définissant la simulation

class Simulation
{
public:

	sf::Image									void_image;		// Image vide
	std::array<sf::Image, THREAD_NB>			images;			// Images où s'affiche la fractale
	std::array<std::atomic<bool>, THREAD_NB>	finished;		// Indique pour chaque thread si il a terminé
	sf::Texture									texture;		// Texture supportant l'image
	sf::Sprite									sprite;			// Sprite servant à afficher la texture
	uint8_t										fractal_type;	// Type de fractale (0 : Mandelbrot, 1 : Julia)
	std::array<Sequence_type, 2>				sequence_types;	// Type de séquence (lié à fractal_type)
	Vector										position;		// Position de la vue
	double										zoom;			// Taille de la vue
	std::vector<Complex>						julia_examples;	// Liste d'exemples d'ensembles de Julia
	uint8_t										example_index;	// Index de la liste d'exemples
	bool										change;			// Dit si il y a eu un changement dans la vue

	Simulation();

	Vector			get_position(const sf::Vector2i& position);
	Vector			window_to_graph(const Vector& position);
	Vector			graph_to_window(const Vector& position);

	uint16_t		sequence_mandelbrot(Complex c, uint16_t iteration_nb);
	uint16_t		sequence_julia(Complex z, uint16_t iteration_nb);
	void			draw_fractal(uint16_t y_min, uint16_t y_max, uint8_t thread_number);
	void			simulate(My_event& my_event);
	void			update(My_event& my_event, sf::Mouse& mouse);

	sf::Color		color(uint16_t value, uint16_t max_value);
	void			draw(sf::RenderWindow& window);
};

#endif