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

extern int screen_width; // Largeur de l'�cran

#define WIDTH			1920							// Largeur de l'�cran
#define HEIGHT			1080							// Hauteeur de l'�cran
#define RESIZE			((1. / 1920.) * screen_width)	// Co�fficent en fonction de la taille de l'�cran
#define FREE_THREAD		2								// Nombre de threads libres

#define MANDELBROT		0
#define JULIA			1
#define SEQUENCE_MAX	2.2								// Valeur limite du modulo du complexe pour arr�ter la suite
#define SEQUENCE_MAX2	5.								// Carr� de la valeur limite du modulo du complexe pour arr�ter la suite

#define HSV_MIN			185								// Couleur min
#define HSV_MAX			271								// Couleur max
#define	HSV_DIFF		86								// Diff�rence entre les deux

typedef uint16_t(Simulation::*Sequence_type)(Complex, uint16_t);

// Classe de gestion d'�v�nements

class My_event
{
public:

	sf::Event*			sf_event;	// Evenement SFML
	sf::RenderWindow*	window;		// Fen�tre SFML
	bool*				end;		// Fin de la simulation
	int16_t*			wheel_move;	// D�placement de la molette
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