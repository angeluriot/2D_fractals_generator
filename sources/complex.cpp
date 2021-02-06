#include "complex.h"

// Construit un complexe

Complex::Complex()
{
	a = 0;
	b = 0;
}

// Construit un complexe à partir d'un autre complexe

Complex::Complex(const Complex& z)
{
	*this = z;
}

// Construit un complexe à partir de ses composantes réelles et imaginaires

Complex::Complex(const double& a, const double& b)
{
	this->a = a;
	this->b = b;
}

// Assignation

void Complex::operator=(const Complex& z)
{
	a = z.a;
	b = z.b;
}

// Donne le module du nombre complexe

double Complex::modulus() const
{
	return sqrt(a * a + b * b);
}

// Donne le module au carré du nombre complexe

double Complex::modulus2() const
{
	return a * a + b * b;
}

// Donne l'angle à l'origine d'un nombre complexe

double Complex::angle() const
{
	return cos(a / modulus());
}

// Assignations

void Complex::operator+=(const Complex& z)
{
	*this = *this + z;
}

void Complex::operator-=(const Complex& z)
{
	*this = *this - z;
}

void Complex::operator*=(const Complex& z)
{
	*this = *this * z;
}

void Complex::operator/=(const Complex& z)
{
	*this = *this / z;
}

void Complex::operator^=(uint16_t n)
{
	*this = *this ^ n;
}

// Addition

Complex operator+(const Complex& z_1, const Complex& z_2)
{
	return Complex(z_1.a + z_2.a, z_1.b + z_2.b);
}

// Soustraction

Complex operator-(const Complex& z_1, const Complex& z_2)
{
	return Complex(z_1.a - z_2.a, z_1.b - z_2.b);
}

// Multiplication

Complex operator*(const Complex& z_1, const Complex& z_2)
{
	return Complex(z_1.a * z_2.a - z_1.b * z_2.b, z_1.a * z_2.b + z_1.b * z_2.a);
}

// Division

Complex operator/(const Complex& z_1, const Complex& z_2)
{
	return Complex((z_1.a * z_2.a + z_1.b * z_2.b) / (pow(z_2.a, 2) + pow(z_2.b, 2)), (z_1.b * z_2.a - z_1.a * z_2.b) / (pow(z_2.a, 2) + pow(z_2.b, 2)));
}

// Exposant

Complex operator^(const Complex& z, uint16_t n)
{
	if (n == 2)
		return Complex(z.a * z.a - z.b * z.b, 2. * z.a * z.b);

	Complex result(1, 0);

	for (uint16_t i = 0; i < n; i++)
		result *= z;

	return result;
}