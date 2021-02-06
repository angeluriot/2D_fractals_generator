#include "utils.h"

// Construit un vecteur

Vector::Vector()
{
	x = 0.;
	y = 0.;
}

// Construit un vecteur à partir d'un autre vecteur

Vector::Vector(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
}

Vector::Vector(const sf::Vector2f& vector)
{
	x = vector.x;
	y = vector.y;
}

Vector::Vector(const sf::Vector2i& vector)
{
	x = vector.x;
	y = vector.y;
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector::Vector(const double& x, const double& y)
{
	this->x = x;
	this->y = y;
}

// Assignations

void Vector::operator=(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
}

void Vector::operator+=(const Vector& vector)
{
	*this = *this + vector;
}

void Vector::operator-=(const Vector& vector)
{
	*this = *this - vector;
}

void Vector::operator*=(const double& number)
{
	*this = *this * number;
}

void Vector::operator/=(const double& number)
{
	*this = *this / number;
}

// Donne la norme du vecteur

double Vector::get_norm() const
{
	return sqrt(x * x + y * y);
}

// Donne l'angle du vecteur (en radiants)

double Vector::get_angle() const
{
	return atan2(y, x);
}

// Modifie la norme du vecteur

void Vector::set_norm(const double& norm)
{
	normalize(*this);

	*this *= norm;
}

// Modifie l'angle du vecteur (en radiants)

void Vector::set_angle(const double& angle)
{
	*this = Vector_polar(get_norm(), angle);
}

// Construit un vecteur à partir de ses coordonnées cartésiennes

Vector Vector_cartesian(const double& x, const double& y)
{
	return Vector(x, y);
}

// Construit un vecteur à partir de ses coordonnées polaires

Vector Vector_polar(const double& norm, const double& angle)
{
	return Vector(get_x(norm, angle), get_y(norm, angle));
}

// Addition

Vector operator+(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x + vector_2.x, vector_1.y + vector_2.y);
}

// Soustraction

Vector operator-(const Vector& vector_1, const Vector& vector_2)
{
	return Vector(vector_1.x - vector_2.x, vector_1.y - vector_2.y);
}

// Produits

Vector operator*(const Vector& vector, const double& number)
{
	return Vector(vector.x * number, vector.y * number);
}

Vector operator*(const double& number, const Vector& vector)
{
	return Vector(number * vector.x, number * vector.y);
}

// Produit scalaire

double operator*(const Vector& vector_1, const Vector& vector_2)
{
	return vector_1.x * vector_2.x + vector_1.y * vector_2.y;
}

// Division

Vector operator/(const Vector& vector, const double& number)
{
	return Vector(vector.x / number, vector.y / number);
}

// Egalités

bool operator==(const Vector& vector_1, const Vector& vector_2)
{
	return (vector_1.x == vector_2.x and vector_1.y == vector_2.y);
}

bool operator!=(const Vector& vector_1, const Vector& vector_2)
{
	return (!(vector_1 == vector_2));
}

// Donne la valeur cartésienne x à partir des coordonnées polaires (en mètres)

double get_x(const double& norm, const double& angle)
{
	return cos(angle) * norm;
}

// Donne la valeur cartésienne y à partir des coordonnées polaires (en mètres)

double get_y(const double& norm, const double& angle)
{
	return sin(angle) * norm;
}

// Donne la distance entre deux points (en mètres)

double get_distance(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_norm();
}

// Donne l'angle phi entre deux points (en radiants)

double get_angle(const Vector& point_1, const Vector& point_2)
{
	return (point_2 - point_1).get_angle();
}

// Donne le vecteur normalisé

Vector normalize(const Vector& vector)
{
	return vector / vector.get_norm();
}

sf::Vector2f to_vector2f(const Vector& vector)
{
	return sf::Vector2f(vector.x, vector.y);
}

sf::Vector2i to_vector2i(const Vector& vector)
{
	return sf::Vector2i(vector.x, vector.y);
}
