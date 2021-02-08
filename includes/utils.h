#ifndef UTILS_H
#define UTILS_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <random>
#include <vector>
#include <iostream>
#include <thread>
#include <mutex>
#include <array>
#include <atomic>
#include <functional>
#include <algorithm>
#include "vector.h"

class Simulation;
class Complex;

extern int screen_width; // Largeur de l'écran

#define WIDTH			1920							// Largeur de l'écran
#define HEIGHT			1080							// Hauteeur de l'écran
#define RESIZE			((1. / 1920.) * screen_width)	// Coéfficent en fonction de la taille de l'écran
#define FREE_THREAD		2								// Nombre de threads libres

#define MANDELBROT		0
#define JULIA			1
#define SEQUENCE_MAX	2.2								// Valeur limite du modulo du complexe pour arrêter la suite
#define SEQUENCE_MAX2	5.								// Carré de la valeur limite du modulo du complexe pour arrêter la suite

#define HSV_MIN			185								// Couleur min
#define HSV_MAX			271								// Couleur max
#define	HSV_DIFF		86								// Différence entre les deux

typedef uint16_t(Simulation::*Sequence_type)(Complex, uint16_t);

// Classe de gestion d'événements

class My_event
{
public:

	sf::Event*			sf_event;	// Evenement SFML
	sf::RenderWindow*	window;		// Fenêtre SFML
	bool*				end;		// Fin de la simulation
	int16_t*			wheel_move;	// Déplacement de la molette
	Simulation*			simulation;	// La simulation

	My_event();
	My_event(const My_event& sf);
	My_event(sf::Event* my_event, sf::RenderWindow* window, bool* end, int16_t* wheel_move, Simulation* simulation);

	void	operator=(const My_event& sf);

	bool	events();
	bool	check();
	bool	wait();
};

int			random_int(int min, int max);
bool		rand_probability(const double& probability);
sf::Color	HSVtoRGB(float fH, float fS, float fV);

#endif