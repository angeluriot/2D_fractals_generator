#ifndef COMPLEX_H
#define COMPLEX_H
#include "utils.h"

// Classe définissant un nombre complexe

class Complex
{
public:

	double a; // Composante réelle
	double b; // Composante imaginaire

	Complex();
	Complex(const Complex& z);
	Complex(const double& a, const double& b);

	void		operator=(const Complex& z);

	double		modulus() const;
	double		modulus2() const;
	double		angle() const;

	void		operator+=(const Complex& z);
	void		operator-=(const Complex& z);
	void		operator*=(const Complex& z);
	void		operator/=(const Complex& z);
	void		operator^=(uint16_t n);
};

Complex		operator+(const Complex& z_1, const Complex& z_2);
Complex		operator-(const Complex& z_1, const Complex& z_2);
Complex		operator*(const Complex& z_1, const Complex& z_2);
Complex		operator/(const Complex& z_1, const Complex& z_2);
Complex		operator^(const Complex& z, uint16_t n);

#endif