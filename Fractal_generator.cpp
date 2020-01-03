#include <windows.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>



// ---------- Affichage ----------



HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

int window_size; // Taille de l'affichage

int Gap_x = 200; // Décalage en X
int Gap_y = 100; // Décalage en Y

double color_constant = 7.; // Constante permettant d'améliorer les couleurs

double sequence_max = 10.; // Le calcul de la suite s'arrête quand elle atteint cette valeur



// Affiche un pixel aux coordonnées voulues

void set_point(const int &x, const int &y, const COLORREF &color)
{
	SetPixel(mydc, Gap_x + x, Gap_y + window_size - y, color);
}



// Donne une couleur à partir du temps que prend la suite à diverger

COLORREF color(int value, const int &max_value)
{
	value *= color_constant;

	value = int(double((double(value) / double(max_value)) * double(255. * 2.)));

	if (value <= 255)
		return RGB(255, 255 - value, 0);

	if (value > 255 and value <= 255 * 2)
		return RGB(2 * 255 - value, 0, value - 255);

	return RGB(0, 0, 0);
}



// Trace un contour blanc

void contour()
{
	for (int i = 0; i < window_size; i++)
	{
		SetPixel(mydc, i + Gap_x, Gap_y, RGB(255, 255, 255));
		SetPixel(mydc, i + Gap_x, Gap_y + window_size + 1, RGB(255, 255, 255));
	}

	for (int j = 0; j < window_size + 2; j++)
	{
		SetPixel(mydc, Gap_x - 1, j + Gap_y, RGB(255, 255, 255));
		SetPixel(mydc, Gap_x + window_size, j + Gap_y, RGB(255, 255, 255));
	}
}



// ---------- Génération de la forme fractale ----------



enum Fractale_type {Julia, Mandelbrot}; // Type de fractale



// Création d'une classe définissant un nombre complexe

class Complex
{
public :

	double a;
	double b;

	Complex()
	{
		a = 0;
		b = 0;
	}

	Complex(const Complex &z)
	{
		a = z.a;
		b = z.b;
	}

	Complex(const double& a, const double& b)
	{
		this->a = a;
		this->b = b;
	}

	void operator=(const Complex &z)
	{
		a = z.a;
		b = z.b;
	}

	double modulus() // Module du nombre complexe
	{
		return sqrt(a * a + b * b);
	}
};

Complex operator+(const Complex &z_1, const Complex &z_2) // Addition
{
	return Complex(z_1.a + z_2.a, z_1.b + z_2.b);
}

Complex operator*(const Complex& z_1, const Complex& z_2) // Multiplication
{
	return Complex(z_1.a * z_2.a - z_1.b * z_2.b, z_1.a * z_2.b + z_1.b * z_2.a);
}



// Calcul la suite d'équation z = z² + c et renvoie le nombre d'itérations pour atteindre "sequence_max"

int sequence(Complex z, const Complex &c, const int &iteration_nb)
{
	for (int i = 0; i < iteration_nb; i++)
	{
		z = z * z + c; // L'équation

		if (z.modulus() > sequence_max)
			return i;
	}

	return iteration_nb;
}



// Affiche l'image en entier de la forme fractale

void show_image(const double &p_x, const double &p_y, const double &graph_size, const int &iteration_nb, const Fractale_type &fractale_type, const Complex &c)
{
	double x = p_x - graph_size / 2.;
	double y = p_y - graph_size / 2.;
	double x_pas = graph_size / double(window_size);
	double y_pas = graph_size / double(window_size);

	for (int i = 0; i < window_size; i++)
	{
		x = p_x - graph_size / 2;
		y += y_pas;

		for (int j = 0; j < window_size; j++)
		{
			x += x_pas;

			int sequence_result;

			if (fractale_type == Julia)
			{
				Complex z = Complex(x, y);
				sequence_result = sequence(z, c, iteration_nb);
			}

			else
			{
				Complex c = Complex(x, y);
				sequence_result = sequence(Complex(0, 0), c, iteration_nb);
			}

			if (sequence_result != iteration_nb)
				set_point(j, i, color(sequence_result, iteration_nb));
		}
	}
}



// ---------- Le main ----------



int main()
{
	// ---------- Choix de l'utilisateur ----------



	window_size = 800;
	color_constant = 7.;

	double x = -0.75;
	double y = 0.;

	double graph_size = 3.;
	int iteration_nb = 250;

	Fractale_type fractale_type = Mandelbrot;
	Complex c = Complex(-0.55, 0.55);



	// ---------- Lancement du programme ----------



	MoveWindow(myconsole, 0, 0, 1920, 1080, TRUE);
	Sleep(100);
	contour();
	show_image(x, y, graph_size, iteration_nb, fractale_type, c);

	std::cout << "finished";

	while (1)
	{}
}
