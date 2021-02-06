#ifndef VECTOR_H
#define VECTOR_H
#include <cmath>
#include <SFML/Graphics.hpp>

#define PI 3.14159265359 // Pi

// Classe définissant un vecteur

class Vector
{
public:

	double x; // coordonnée x
	double y; // coordonnée y

	// Constructeurs

	Vector();
	Vector(const Vector& vector);
	Vector(const sf::Vector2f& vector);
	Vector(const sf::Vector2i& vector);
	Vector(const double& x, const double& y);

	// Assignations

	void		operator=(const Vector& vector);
	void		operator+=(const Vector& vector);
	void		operator-=(const Vector& vector);
	void		operator*=(const double& number);
	void		operator/=(const double& number);

	// Récupérer

	double		get_norm() const;
	double		get_angle() const;

	// Modifier

	void		set_norm(const double& norm);
	void		set_angle(const double& angle);
};

// Constructeurs

Vector			Vector_cartesian(const double& x, const double& y);
Vector			Vector_polar(const double& norm, const double& angle);

// Opérateurs

Vector			operator+(const Vector& vector_1, const Vector& vector_2);
Vector			operator-(const Vector& vector_1, const Vector& vector_2);
Vector			operator*(const Vector& vector, const double& number);
Vector			operator*(const double& number, const Vector& vector);
double			operator*(const Vector& vector_1, const Vector& vector_2);
Vector			operator/(const Vector& vector, const double& number);
bool			operator==(const Vector& vector_1, const Vector& vector_2);
bool			operator!=(const Vector& vector_1, const Vector& vector_2);

// Récupérer

double			get_x(const double& norm, const double& angle);
double			get_y(const double& norm, const double& angle);
double			get_distance(const Vector& point_1, const Vector& point_2);
double			get_angle(const Vector& point_1, const Vector& point_2);

// Autres fonctions

Vector			normalize(const Vector& vector);
sf::Vector2f	to_vector2f(const Vector& vector);
sf::Vector2i	to_vector2i(const Vector& vector);

#endif