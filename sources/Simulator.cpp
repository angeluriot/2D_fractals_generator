#include "Simulator.hpp"

Fractal*				Simulator::fractal;
double					Simulator::area_width;
std::array<double, 2>	Simulator::position;
bool					Simulator::moving_point;
bool					Simulator::image_done;

void Simulator::init()
{
	ComputeShader::init("shaders/compute/cl_compute_shader.cl");
	Fractal::image.reset(dim::Window::get_size().x, dim::Window::get_size().y);

	Renderer::init();
	fractal = new Julia();
	reset();
}

void Simulator::reset()
{
	dim::Window::set_cull_face(false);
	moving_point = false;
	area_width = 5.;
	position = { 0., 0. };
	fractal->reset();
	image_done = false;
}

std::array<double, 2> Simulator::screen_to_world(dim::Vector2int pos)
{
	double area_height = area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	double x = (((double)pos.x / (double)dim::Window::get_size().x) - 0.5) * area_width + position[0];
	double y = (((double)(dim::Window::get_size().y - pos.y) / (double)dim::Window::get_size().y) - 0.5) * area_height + position[1];

	return { x, y };
}

dim::Vector2int Simulator::world_to_screen(std::array<double, 2> pos)
{
	double area_height = area_width * ((double)dim::Window::get_size().y / (double)dim::Window::get_size().x);

	int x = (((pos[0] - position[0]) / area_width) + 0.5) * dim::Window::get_size().x;
	int y = dim::Window::get_size().y - ((((pos[1] - position[1]) / area_height) + 0.5) * dim::Window::get_size().y);

	return dim::Vector2int(x, y);
}

void Simulator::update()
{
	static dim::Vector2int prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	dim::Vector2int mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Menu::active && mouse_pos.x >= 0 && mouse_pos.x <= dim::Window::get_size().x &&
		mouse_pos.y >= 0 && mouse_pos.y <= dim::Window::get_size().y && !moving_point && fractal->get_type() != Fractal::Type::Buddhabrot)
	{
		position[0] -= screen_to_world(mouse_pos)[0] - screen_to_world(prev_mouse_pos)[0];
		position[1] -= screen_to_world(mouse_pos)[1] - screen_to_world(prev_mouse_pos)[1];
		image_done = false;
	}

	prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());
}

void Simulator::check_events(const sf::Event& sf_event)
{
	if (sf_event.type == sf::Event::MouseWheelMoved)
	{
		float zoom;

		if (sf_event.mouseWheel.delta > 0)
			zoom = 0.95f;
		else
			zoom = 1.05f;

		std::array<double, 2> prev_mouse_pos = screen_to_world(sf::Mouse::getPosition(dim::Window::get_window()));

		for (int i = 0; i < std::abs(sf_event.mouseWheel.delta); i++)
			area_width *= zoom;

		std::array<double, 2> mouse_pos = screen_to_world(sf::Mouse::getPosition(dim::Window::get_window()));

		position[0] -= mouse_pos[0] - prev_mouse_pos[0];
		position[1] -= mouse_pos[1] - prev_mouse_pos[1];

		image_done = false;
	}

	if (sf_event.type == sf::Event::Resized)
	{
		Fractal::image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
		image_done = false;
	}

	if (sf_event.type == sf::Event::KeyPressed && sf_event.key.code == sf::Keyboard::F2)
	{
		Fractal::image.save("screens");
	}

	if (sf_event.type == sf::Event::MouseButtonPressed && sf_event.key.code == sf::Mouse::Right && Simulator::fractal->get_type() == Fractal::Type::Mandelbrot)
	{
		auto pos = screen_to_world(sf::Mouse::getPosition(dim::Window::get_window()));
		delete fractal;
		fractal = new Julia();
		reset();
		((Julia*)Simulator::fractal)->c[0] = pos[0];
		((Julia*)Simulator::fractal)->c[1] = pos[1];
	}
}

void Simulator::draw()
{
	if (!image_done)
	{
		Simulator::fractal->compute();
		image_done = true;
	}

	Renderer::draw();
}
