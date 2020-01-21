#include "complex.h"
#include "SDL.h"



// Construit un complexe

Complex::Complex()
{
	a = 0;
	b = 0;
}



// Construit un complexe à partir d'un autre complexe

Complex::Complex(const Complex& z)
{
	a = z.a;
	b = z.b;
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

double Complex::modulus()
{
	return sqrt(a * a + b * b);
}



// Addition

Complex operator+(const Complex& z_1, const Complex& z_2)
{
	return Complex(z_1.a + z_2.a, z_1.b + z_2.b);
}



// Multiplication

Complex operator*(const Complex& z_1, const Complex& z_2)
{
	return Complex(z_1.a * z_2.a - z_1.b * z_2.b, z_1.a * z_2.b + z_1.b * z_2.a);
}