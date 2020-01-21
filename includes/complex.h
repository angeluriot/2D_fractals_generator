#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
#include "SDL.h"

class Complex
{
public:

	double a; // Composante réelle
	double b; // Composante imaginaire

	Complex();
	Complex(const Complex& z);
	Complex(const double& a, const double& b);

	void operator=(const Complex& z);

	double modulus();
};

Complex operator+(const Complex& z_1, const Complex& z_2);
Complex operator*(const Complex& z_1, const Complex& z_2);

#endif