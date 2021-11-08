#include "Simulator.hpp"

Fractal*		Simulator::fractal;
float			Simulator::area_width;
dim::Vector2	Simulator::position;
bool			Simulator::image_done;

void Simulator::init()
{
	Fractal::mesh = dim::Mesh::screen;
	Fractal::mesh.texcoords[0] = dim::Vector2( 0.5f,  0.5f);
	Fractal::mesh.texcoords[1] = dim::Vector2(-0.5f,  0.5f);
	Fractal::mesh.texcoords[2] = dim::Vector2(-0.5f, -0.5f);
	Fractal::mesh.texcoords[3] = dim::Vector2( 0.5f, -0.5f);
	Fractal::mesh.texcoords[4] = dim::Vector2( 0.5f,  0.5f);
	Fractal::mesh.texcoords[5] = dim::Vector2(-0.5f, -0.5f);

	Renderer::init();
	fractal = new Julia();
	reset();
}

void Simulator::reset()
{
	area_width = 4.f;
	position = dim::Vector2(0.f, 0.f);
	fractal->reset();
	image_done = false;
}

dim::Vector2 Simulator::screen_to_world(dim::Vector2int pos)
{
	float x = ((pos.x / static_cast<float>(dim::Window::get_size().x)) - 0.5f) * area_width + position.x;
	float y = (0.5f - (pos.y / static_cast<float>(dim::Window::get_size().x))) * area_width + position.y;

	return dim::Vector2(x, y);
}

dim::Vector2int Simulator::world_to_screen(dim::Vector2 pos)
{
	float x = (((pos.x - position.x) / area_width) + 0.5f) * static_cast<float>(dim::Window::get_size().x);
	float y = (1.5f - ((pos.y - position.y) / area_width)) * static_cast<float>(dim::Window::get_size().x);
	return dim::Vector2(x, y);
}

void Simulator::update()
{
	static dim::Vector2int prev_mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	dim::Vector2int mouse_pos = sf::Mouse::getPosition(dim::Window::get_window());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !Menu::active && mouse_pos.x >= 0 && mouse_pos.x <= dim::Window::get_size().x &&
		mouse_pos.y >= 0 && mouse_pos.y <= dim::Window::get_size().y)
	{
		position -= screen_to_world(mouse_pos) - screen_to_world(prev_mouse_pos);
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

	Renderer::check_events(sf_event);
}

void Simulator::draw()
{
	if (!image_done)
	{
		Simulator::fractal->render();
		image_done = true;
	}

	Renderer::draw();
}
