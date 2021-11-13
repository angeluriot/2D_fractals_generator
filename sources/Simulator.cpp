#include "Simulator.hpp"

Fractal*				Simulator::fractal;
double					Simulator::area_width;
std::array<double, 2>	Simulator::position;
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
	area_width = 4.;
	position = { 0., 0. };
	fractal->reset();
	image_done = false;
}

std::array<double, 2> Simulator::screen_to_world(dim::Vector2int pos)
{
	double x = ((static_cast<double>(pos.x) / static_cast<double>(dim::Window::get_size().x)) - 0.5) * area_width + position[0];
	double y = (0.5 - (static_cast<double>(pos.y) / static_cast<double>(dim::Window::get_size().x))) * area_width + position[1];

	return { x, y };
}

dim::Vector2int Simulator::world_to_screen(std::array<double, 2> pos)
{
	int x = (((pos[0] - position[0]) / area_width) + 0.5) * dim::Window::get_size().x;
	int y = (1.5 - ((pos[1] - position[1]) / area_width)) * dim::Window::get_size().x;
	return dim::Vector2int(x, y);
}

void Simulator::update()
{
	static dim::Vector2int prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	dim::Vector2int mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Menu::active && mouse_pos.x >= 0 && mouse_pos.x <= dim::Window::get_size().x &&
		mouse_pos.y >= 0 && mouse_pos.y <= dim::Window::get_size().y)
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

		for (int i = 0; i < std::abs(sf_event.mouseWheel.delta); i++)
			area_width *= zoom;

		image_done = false;
	}

	if (sf_event.type == sf::Event::Resized)
	{
		Fractal::image.reset(dim::Window::get_size().x, dim::Window::get_size().y);
		image_done = false;
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